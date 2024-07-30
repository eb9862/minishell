/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 19:52:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pids(pid_t *pids)
{
	free(pids);
}

int	is_contain_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	handle_line(char *line, char **envp, int *status)
{
	t_process_list	*process_list;
	t_q_token_list	*token_list;
	pid_t			*pids;

	(void) envp;
	if (is_contain_quotes(line))
	{
		if (!delegate_quotes_syntax_check(line))
			return ;
	}
	token_list = get_expand_line(line, status);
	if (!token_list)
		return ;
	process_list = get_process_list(token_list);
	if (!process_list)
		return ;
	pids = malloc(sizeof(pid_t) * process_list -> count);
	if (!pids)
	{
		clear_pl_tl(token_list, process_list);
		return ;
	}
	handle_process(process_list, envp, status, pids);
	(clear_pl_tl(token_list, process_list), free_pids(pids));
}
