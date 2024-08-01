/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 19:53:35 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_res_path(char *path, char *p_name, char **paths)
{
	int		size;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = get_content_len(path) + get_content_len(p_name) + 1;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		free_split(paths);
		return (0);
	}
	while (path[j])
		res[i++] = path[j++];
	res[i++] = '/';
	j = 0;
	while (p_name[j])
		res[i++] = p_name[j++];
	res[i] = 0;
	return (res);
}

char	*get_path_name(char *p_name)
{
	char	**paths;
	int		i;
	char	*tmp_path;

	i = 0;
	paths = get_paths();
	if (!paths)
		return (0);
	while (paths[i])
	{
		tmp_path = get_res_path(paths[i], p_name, paths);
		if (!tmp_path)
			return (0);
		if (access(tmp_path, F_OK) == 0 && access(tmp_path, X_OK) == 0)
		{
			free_split(paths);
			return (tmp_path);
		}
		free(tmp_path);
		i++;
	}
	free_split(paths);
	if (access(p_name, F_OK) == 0 && access(p_name, X_OK) == 0)
		return (p_name);
	(handle_not_found_pg_or_directory(p_name), exit(127));
}

void	excute_cmd(t_process_info *process, char **envp, pid_t pids[])
{
	int		fd[2];
	pid_t	pid;
	char	*path_name;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	signal(SIGQUIT, sigquit_in_process);
	signal(SIGINT, sigint_in_process);
	pids[process -> idx] = pid;
	if (pid == 0)
	{
		close(fd[0]);
		path_name = get_path_name(process -> program_name);
		if (process -> next)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		if (process -> is_redirected)
			set_stream(process -> in, process -> out);
		execve(path_name, process -> argv, envp);
		free(path_name);
	}
	else
		(close(fd[1]), dup2(fd[0], STDIN_FILENO), close(fd[0]));
}

// void	excute_built_in(t_process_info *process, pid_t pids[], t_env_list *el)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		return ;
// 	pid = fork();
// 	signal(SIGQUIT, sigquit_in_process); // test
// 	signal(SIGINT, sigint_in_process); // test too
// 	pids[process -> idx] = pid;
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		if (process -> next)
// 			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
// 		if (process -> is_redirected)
// 			set_stream(process -> in, process -> out);
// 		run_built_in(process, el);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
// 	}
// }

void	excute_child_process(t_process_info *process, char **envp, \
	pid_t pids[], t_env_list *el)
{
	if (is_buitin(process -> program_name) == -1)
		excute_cmd(process, envp, pids);
	else
		excute_built_in(process, pids, el);
}

void	handle_process(t_process_list *process_list, \
	char **envp, t_env_list *el, pid_t *pids)
{
	t_process_info	*process;
	int				original_in;
	int				original_out;
	int				i;

	i = -1;
	process = process_list -> head;
	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	while (process)
	{
		++i;
		excute_child_process(process, envp, pids, el);
		process = process -> next;
	}
	i = -1;
	while (++i < process_list -> count)
	{
		if (pids[i] != -1)
			waitpid(pids[i], &g_status, 0);
		set_signal();
	}
	(dup2(original_in, STDIN_FILENO), dup2(original_out, STDOUT_FILENO));
	(close(original_in), close(original_out));
}
