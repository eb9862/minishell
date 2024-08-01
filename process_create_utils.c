/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_create_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:29 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 16:40:49 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_pl_tl(t_q_token_list *token_list, t_process_list *process_list)
{
	clear_q_token_list(token_list);
	clear_process_list(process_list);
}

int	get_plain_count(t_q_token_list *list)
{
	t_q_token	*now;
	int			pc;

	pc = 0;
	now = list -> head;
	while (now)
	{
		if (now -> type == PLAIN)
			pc++;
		now = now -> next;
	}
	return (pc);
}

void	add_process_last(t_process_list *list, t_process_info *process)
{
	t_process_info	*now;

	if (!list -> head)
	{
		list -> head = process;
		list -> tail = process;
	}
	else
	{
		now = list -> head;
		while (now -> next)
			now = now -> next;
		now -> next = process;
		list -> tail = process;
	}
	process -> idx = list -> count;
	list -> count++;
}

int	set_cmd(t_process_info *process, t_q_token *st, \
	t_q_token *et, int cmd_count)
{
	char		**argv;
	t_q_token	*now;
	int			i;

	i = 0;
	now = st;
	argv = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!argv)
		return (0);
	while (now != et)
	{
		if (now -> type == PLAIN)
			argv[i++] = now -> content;
		now = now -> next;
	}
	argv[i] = 0;
	process -> program_name = argv[0];
	process -> argv = argv;
	return (1);
}
