/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/16 02:02:48 by joojeon          ###   ########.fr       */
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
	while(envp[i])
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

void print_paths(char **s)
{
	int i = 0;

	while(s[i]){
		printf("path = %s\n", s[i]);
		i++;
	}
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
		//누수 잡아야 함 <- join
		tmp_path = ft_strjoin(ft_strjoin(paths[i], "/"), p_name);
		if (access(tmp_path, F_OK) == 0 && access(tmp_path, X_OK) == 0)
		{
			free_split(paths);
			return (tmp_path);
		}
		i++;
	}
	free_split(paths);
	return (0);
}


void	set_stream(int in, int out, int *fd)
{
	(void) fd;
	if (in != 0)
		dup2(in, STDIN_FILENO);
	if (out != 1)
		dup2(out, 1);
}

void	excute_child_process(t_process_info *process, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	*path_name;

	if (pipe(fd) == -1)
		return ;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		printf("process in = %d out = %d\n", process -> in , process -> out);
		if (process -> next)
			dup2(fd[1], STDOUT_FILENO);
		path_name = get_path_name(process -> program_name, envp);
		if (process -> is_redirected)
			set_stream(process -> in, process -> out, fd);
		execve(path_name, process -> argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

void	handle_process(t_process_list *process_list, char **envp)
{
	t_process_info	*process;
	int		original_in;
	int		original_out;

	process = process_list -> head;
	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	while (process)
	{
		excute_child_process(process, envp);
		process = process -> next;
	}
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	close(original_in);
	close(original_out);
}
