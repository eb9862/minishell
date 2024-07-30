/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:24:51 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/31 00:21:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

int	expand_plain(t_q_token_list *list)
{
	t_q_token	*now;
	int			dollar_idx;

	now = list -> head;
	while (now)
	{
		if (now -> type == PLAIN)
		{
			dollar_idx = get_dollar_sign_idx(now -> content);
			if (dollar_idx != -1)
			{
				now -> content = get_expanded_content(now -> content, \
					dollar_idx);
				if (!now -> content)
				{
					clear_q_token_list(list);
					return (0);
				}
			}
		}
		now = now -> next;
	}
	return (1);
}
