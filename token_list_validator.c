/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_validator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:07:58 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/31 16:17:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_pipe_syntax(t_q_token_list *list)
{
	t_q_token	*now;
	t_q_token	*prev;

	now = list -> head;
	prev = NULL;
	while (now)
	{
		if (now -> type == PIP)
		{
			if (!prev || !now -> next || now -> next -> type == PIP)
			{
				handle_pipe_error();
				return (0);
			}
		}
		prev = now;
		now = now -> next;
	}
	return (1);
}

int	is_valid_rdrt_token(t_q_token_list *list)
{
	t_q_token	*now;

	now = list -> head;
	while (now)
	{
		if (now -> type == RDRT_AO || now -> type == RDRT_TO || \
			now -> type == RDRT_HD || now -> type == RDRT_IN)
		{
			if (!now -> next)
			{
				handle_missed_file_error();
				return (0);
			}
			else if (now -> next -> type == RDRT_AO || now ->  next -> \
				type == RDRT_TO || now -> next -> type == RDRT_HD || now ->\
			 	next -> type == RDRT_IN )
			{
				handle_rdrt_err(now -> next -> content);
				return (0);
			}
		}
		now = now -> next;
	}
	return (1);
}

int	is_file_missed(t_q_token_list *list)
{
	t_q_token	*now;

	now = list -> head;
	while (now)
	{
		if (now -> type == RDRT_AO || now -> type == RDRT_TO || \
			now -> type == RDRT_IN || now -> type == RDRT_HD)
		{
			if (!now -> next)
			{
				handle_missed_file_error();
				return (1);
			}
		}
		now = now -> next;
	}
	return (0);
}

int	validate_token_list(t_q_token_list *list)
{
	if (!is_valid_rdrt_token(list))
	{
		clear_q_token_list(list);
		return (0);
	}
	if (is_file_missed(list))
	{
		clear_q_token_list(list);
		return (0);
	}
	if (!is_valid_pipe_syntax(list))
	{
		clear_q_token_list(list);
		return (0);
	}
	return (1);
}
