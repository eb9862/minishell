/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:27:04 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 02:32:18 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_q_token(t_q_token *token)
{
	free(token -> content);
	token -> next = NULL;
}

void	clear_q_token_list(t_q_token_list *list)
{
	t_q_token	*now;
	t_q_token	*tmp;

	now = list -> head;
	while (now)
	{
		tmp = now -> next;
		clear_q_token(now);
		now = tmp;
	}
	free(list);
}
