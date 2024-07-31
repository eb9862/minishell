/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/31 19:00:33 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

int		is_buitin(char *p_name)
{
	if (ft_strncmp("echo", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("echo") == get_content_len(p_name)))
		return (ECHO);
	if (ft_strncmp("cd", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("cd") == get_content_len(p_name)))
		return (CD);
	if (ft_strncmp("pwd", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("pwd") == get_content_len(p_name)))
		return (PWD);
	if (ft_strncmp("export", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("export") == get_content_len(p_name)))
		return (EXPORT);
	if (ft_strncmp("unset", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("unset") == get_content_len(p_name)))
		return (UNSET);
	if (ft_strncmp("env", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("env") == get_content_len(p_name)))
		return (ENV);
	if (ft_strncmp("exit", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("exit") == get_content_len(p_name)))
		return (EXIT);
	return (-1);
}

char	**get_paths()
{
	char	*path_line;
	char	**split;

	path_line = getenv("PATH");
	split = ft_split(path_line, ':');
	if (!split)
		return (0);
	return (split);
}

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

int	is_contains_slash(char *p_name)
{
	int	i;

	i = 0;
	while (p_name[i])
	{
		if (p_name[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	handle_not_found_pg_or_directory(char *p_name)
{
	if (is_contains_slash(p_name))
	{
		write(2, "porschell: ", get_content_len("porschell: "));
		write(2, p_name, get_content_len(p_name));
		write(2, ": No such file or directory\n", get_content_len(": No such file or directory\n"));
	}
	else
	{
		write(2, p_name, get_content_len(p_name));
		write(2, ": command not found\n", get_content_len(": command not found\n"));
	}
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
	handle_not_found_pg_or_directory(p_name);
	exit(127);
}

void	set_stream(int in, int out)
{
	if (in != 0)
		dup2(in, STDIN_FILENO);
	if (out != 1)
		dup2(out, 1);
}

void	excute_cmd(t_process_info *process, char **envp, pid_t pids[])
{
	int		fd[2];
	pid_t	pid;
	char	*path_name;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	signal(SIGQUIT, sigquit_in_process); // test
	signal(SIGINT, sigint_in_process); // test too
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
	{
		close(fd[1]);
		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
	}
}

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	run_built_in(t_process_info *process, t_env_list *el)
{
	int	argc;
	int	type;

	argc = get_argc(process -> argv);
	type = is_buitin(process -> program_name);
	if (type == ECHO)
		echo(argc, process -> argv); // 매개변수 수정 필요
	if (type == CD)
		cd(argc, process -> argv, el);
	if (type == PWD)
		pwd(el);
	if (type == EXPORT)
		export(argc, el, process -> argv); // 매개변수로 env_list를 받는데 현재 전달 불가
	if (type == UNSET)
		unset(argc, process -> argv, el); // export와 같음
	if (type == ENV)
		env(el); // unset와 같음
	if (type == EXIT)
		bi_exit(argc, process -> argv);
}

void	excute_built_in(t_process_info *process, pid_t pids[], t_env_list *el)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	signal(SIGQUIT, sigquit_in_process); // test
	signal(SIGINT, sigint_in_process); // test too
	pids[process -> idx] = pid;
	if (pid == 0)
	{
		close(fd[0]);
		if (process -> next)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		if (process -> is_redirected)
			set_stream(process -> in, process -> out);
		run_built_in(process, el);
		exit(0);
	}
	else
	{
		close(fd[1]);
		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
	}
}

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
		waitpid(pids[i], &status, 0);
		set_signal(); // test
	}
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	close(original_in);
	close(original_out);
}
