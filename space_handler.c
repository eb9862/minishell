/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:56:28 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/25 13:09:45 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_space(t_q_token_list *list)
{
	t_q_token	*now;
	t_q_token	*prev;

	now = list -> head;
	prev = NULL;
	while (now)
	{
		if (now -> type == SPACE_TYPE)
		{
			if (!prev)
				list -> head = now -> next;
			else
				prev -> next = now -> next;
			clear_q_token(now);
			now = list -> head;
		}
		else
		{
			prev = now;
			now = now -> next;
		}
	}
}
