/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:50:09 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 17:53:56 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test code
int	is_only_dollar(char *content)
{
	int	l;

	l = get_content_len(content);
	if (l == 1 && content[0] == '$')
		return (1);
	return (0);
}
// test code end #######################################

int	is_dollar_question(char *content, int dollar_idx)
{
	if (content[dollar_idx] == '$' && content[dollar_idx + 1] == '?')
		return (1);
	return (0);
}

char	*get_expanded_content(char *content, int dollar_idx)
{
	char	*only_env;
	char	*expanded_content;
	char	*c_status;

	if (is_dollar_question(content, dollar_idx))
	{
		c_status = ft_itoa(g_status >> 8);
		if (!c_status)
			return (0);
		expanded_content = get_new_content_ds(content, dollar_idx, c_status);
		free(c_status);
	}
	else if (is_only_dollar(content)) // test code ###############
	{
		expanded_content = malloc(sizeof(char) * 2);
		expanded_content[0] = '$';
		expanded_content[1] = '\0';
	}
	else // test code end #############################
	{
		only_env = get_only_env(content + dollar_idx + 1);
		if (!only_env)
			return (0);
		expanded_content = get_new_content(content, \
			dollar_idx, getenv(only_env));
		free(only_env);
	}
	free(content);
	return (expanded_content);
}

int	expand_content(t_q_token *token)
{
	int	dollar_idx;

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
			if (!expand_content(now))
			{
				clear_q_token_list(list);
				return (0);
			}
		}
		now = now -> next;
	}
	return (1);
}
