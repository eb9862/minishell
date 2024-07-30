/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 16:48:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pids(pid_t *pids)
{
	free(pids);
}

void	handle_line(char *line, char **envp, int *status)
{
	t_process_list	*process_list;
	t_q_token_list	*token_list;
	pid_t			*pids;

	(void) envp;
	if (!check_quotes_syntax(line))
	{
		printf("syntax error : quotes error!!!!!!!\n");
		return ;
	}
	token_list = get_expand_line(line, status);
	if (!token_list)
		return ;
	// if (!validate(token_list))
	// 	return ;
	process_list = get_process_list(token_list);
	if (!process_list)
		return ;
	pids = malloc(sizeof(pid_t) * process_list -> count);
	if (pids == NULL)
		return ;// 임시
	handle_process(process_list, envp, status, pids);
	clear_pl_tl(token_list, process_list);
	free_pids(pids);
}
