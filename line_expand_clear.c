/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:27:04 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 16:46:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_q_token(t_q_token *token)
{
	free(token -> content);
	if (token -> fd != -1)
		close(token -> fd);
	free(token);
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
	unlink("tmp_file");
}
