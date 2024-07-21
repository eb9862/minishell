/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/20 16:47:28 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*path_line;
	char	**split;

	i = 0;
	path_line = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path_line = envp[i];
			break ;
		}
		i++;
	}
	split = ft_split(path_line + 5, ':');
	if (!split)
		return (0);
	return (split);
}

char	*get_path_name(char *p_name, char **envp)
{
	char	**paths;
	int		i;
	char	*tmp_path;

	i = 0;
	paths = get_paths(envp);
	if (!paths)
		return (0);
	while (paths[i])
	{
		tmp_path = ft_strjoin(ft_strjoin(paths[i], "/"), p_name);
		if (access(tmp_path, F_OK) == 0 && access(tmp_path, X_OK) == 0)
		{
			free_split(paths);
			return (tmp_path);
		}
		i++;
	}
	free_split(paths);
	printf("%s : command not found\n", p_name);
	exit(127);
	return (0);
}

void	set_stream(int in, int out)
{
	if (in != 0)
		dup2(in, STDIN_FILENO);
	if (out != 1)
		dup2(out, 1);
}

void	excute_child_process(t_process_info *process, char **envp, \
	pid_t pids[], int i)
{
	int		fd[2];
	pid_t	pid;
	char	*path_name;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	pids[i] = pid;
	if (pid == 0)
	{
		close(fd[0]);
		path_name = get_path_name(process -> program_name, envp);
		if (process -> next)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		if (process -> is_redirected)
			set_stream(process -> in, process -> out);
		execve(path_name, process -> argv, envp);
	}
	else
	{
		close(fd[1]);
		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
	}
}

void	handle_process(t_process_list *process_list, \
	char **envp, int *status, int count)
{
	t_process_info	*process;
	int				original_in;
	int				original_out;
	int				i;
	pid_t			pids[count];

	i = -1;
	process = process_list -> head;
	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	while (process)
	{
		++i;
		excute_child_process(process, envp, pids, i);
		process = process -> next;
	}
	i = -1;
	while (++i < process_list -> count)
		waitpid(pids[i], status, 0);
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	close(original_in);
	close(original_out);
}
