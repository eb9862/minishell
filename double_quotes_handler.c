/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:06:04 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 01:05:30 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expanded_content(char *content, int dollar_idx)
{
	char	*only_env;
	char	*expanded_content;

	only_env = get_only_env(content + dollar_idx + 1);
	if (!only_env)
		return (0);
	expanded_content = get_new_content(content, dollar_idx, getenv(only_env));
	return (expanded_content);
}

int expand_content(t_q_token *token)
{
    int		dollar_idx;

    dollar_idx = get_dollar_sign_idx(token -> content);
    if (dollar_idx != -1)
	{
		token -> content = get_expanded_content(token -> content, dollar_idx);
		token -> content_len = ft_strlen(token -> content);
		if (!token -> content)
			return (0);
	}
	change_double2single(token -> content);
	token -> type = SINGLE_QUOTES;
	return (1);
}

int	expand_double_quotes(t_q_token_list *list)
{
	t_q_token	*now;

	now = list -> head;
	while (now)
	{
		if (now -> type == DOUBLE_QOUTES)
		{
			if(!expand_content(now))
                return (0);
		}
        now = now -> next;
	}
    return (1);
}
