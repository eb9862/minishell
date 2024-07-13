/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info_creator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:59:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/14 01:48:04 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process_list	*create_process_list(void)
{
	t_process_list	*process_list;

	process_list = (t_process_list *)malloc(sizeof(t_process_list));
	if (!process_list)
		return (0);
	process_list -> head = NULL;
	process_list -> tail = NULL;
	return (process_list);
}

t_process_info	*create_process_info(void)
{
	t_process_info	*process_info;

	process_info = (t_process_info *)malloc(sizeof(t_process_info));
	if (!process_info)
		return (0);
	process_info -> program_name = NULL;
	process_info -> argv = NULL;
	process_info -> is_redirected = 0;
	process_info -> in = 0;
	process_info -> out = 1;
	process_info -> infile_name = NULL;
	process_info -> outfile_name = NULL;
	process_info -> next = NULL;
	return (process_info);
}

int	regist_process(t_process_list *list, t_token *st, \
	t_token *et, t_token_list *token_list)
{
	t_process_info	*process_info;
	t_token			*now;

	process_info = create_process_info();
	if (!process_info)
		return (0);
	now = st;
	while (now != et)
	{
		if (now -> type == CMD \
			|| now -> type == FILE_CONTENT || now -> type == DELEMETER)
		{
			if (!set_str_data(process_info, now, token_list))
				return (0);
		}
		if (now -> type == RDRT_APPEND_OUT \
			|| now -> type == RDRT_TRUNC_OUT || now -> type == RDRT_INPUT)
			process_info -> is_redirected = 1;
		now = now -> next;
	}
	add_process_last(list, process_info);
	return (1);
}

t_process_list	*get_process_list(t_token_list *token_list)
{
	t_process_list	*process_list;
	t_token			*s_token;
	t_token			*e_token;

	s_token = token_list -> head;
	e_token = token_list -> head;
	process_list = create_process_list();
	if (!process_list)
	{
		clear_token_list(token_list);
		return (0);
	}
	while (e_token)
	{
		while (e_token && e_token -> type != PIPE)
			e_token = e_token -> next;
		if (!regist_process(process_list, s_token, e_token, token_list))
			return (0);
		if (e_token)
		{
			s_token = e_token -> next;
			e_token = e_token -> next;
		}
	}
	return (process_list);
}
