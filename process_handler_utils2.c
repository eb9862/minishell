/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:29:07 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 22:29:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_multiple_process(t_process_list *process_list, char **envp, \
	pid_t *pids, t_env_list *el)
{
	int i = -1;
	t_process_info *process;

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
			waitpid(pids[i], &g_status, 0);
	}
}

void	handle_single_built_in(t_process_info *process, t_env_list *el)
{
	if (process -> is_redirected)
		set_stream(process -> in, process -> out);
	run_built_in(process, el);
}