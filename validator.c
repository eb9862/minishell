/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:47:19 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 23:19:35 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_rdrt_syntax(t_token_list *token_list)
{
	t_token	*token;

	token = token_list -> head;
	while (token)
	{
		if (is_redirection(token -> type))
		{
			if (!token -> next)
			{
				redirection_newline_error();
				return (0);
			}
			else
			{
				if (is_redirection(token -> next -> type) || \
					token -> next -> type == PIPE)
				{
					redirection_chaining_error(token -> next -> type);
					return (0);
				}
			}
		}
		token = token -> next;
	}
	return (1);
}

int	check_pipe_syntax(t_token_list *token_list)
{
	t_token	*token;
	t_token	*prev_token;

	prev_token = NULL;
	token = token_list -> head;
	while (token)
	{
		if (token -> type == PIPE)
		{
			if (prev_token == NULL)
			{
				pipe_error();
				return (0);
			}
		}
		prev_token = token;
		token = token -> next;
	}
	return (1);
}

int	validate(t_token_list *token_list)
{
	if (!check_pipe_syntax(token_list))
	{
		clear_token_list(token_list);
		return (0);
	}
	if (!check_rdrt_syntax(token_list))
	{
		clear_token_list(token_list);
		return (0);
	}
	return (1);
}
