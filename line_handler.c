/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonwan <joonwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:48:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/06 16:20:21 by joonwan          ###   ########.fr       */
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

void	handle_line(char *line, char **envp, t_env_list *el)
{
	t_process_list	*process_list;
	t_q_token_list	*token_list;
	pid_t			*pids;

	if (is_contain_quotes(line))
	{
		if (!delegate_quotes_syntax_check(line))
			return ;
	}
	token_list = get_expand_line(line);
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
	handle_process(process_list, envp, el, pids);
	(clear_pl_tl(token_list, process_list), free_pids(pids));
}
