/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/02 02:38:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_cmd(t_process_info *process, char **envp, pid_t pids[])
{
	int		fd[2];
	pid_t	pid;
	char	*path_name;

	if (pipe(fd) == -1)
		return ;
	ignore_parent_signal();
	pid = fork();
	pids[process -> idx] = pid;
	signal(SIGQUIT, sigquit_in_process);
	signal(SIGINT, sigint_in_process);
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

void	excute_child_process(t_process_info *process, char **envp, \
	pid_t pids[], t_env_list *el)
{
	if (is_buitin(process -> program_name) == -1)
		excute_cmd(process, envp, pids);
	else
		excute_built_in(process, pids, el);
}

void	handle_multiple_process(t_process_list *process_list, char **envp, \
	pid_t *pids, t_env_list *el)
{
	int				i;
	t_process_info	*process;

	i = -1;
	process = process_list -> head;
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
		{
			waitpid(pids[i], &g_status, 0);
			if ((g_status & 255) != 0)
				g_status = (g_status + 128) << 8;
			set_signal();
		}
	}
}

void	handle_single_built_in(t_process_info *process, t_env_list *el)
{
	if (process -> is_redirected)
		set_stream(process -> in, process -> out);
	run_built_in(process, el, 1);
}

void	handle_process(t_process_list *process_list, \
	char **envp, t_env_list *el, pid_t *pids)
{
	int				original_in;
	int				original_out;

	save_original(&original_in, &original_out);
	if (process_list -> count == 1 && \
		is_buitin(process_list -> head -> program_name) != -1)
		handle_single_built_in(process_list -> head, el);
	else
		handle_multiple_process(process_list, envp, pids, el);
	(dup2(original_in, STDIN_FILENO), dup2(original_out, STDOUT_FILENO));
	(close(original_in), close(original_out));
}
