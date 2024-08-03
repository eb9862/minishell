/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_clear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:50:37 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 16:50:38 by eunhwang         ###   ########.fr       */
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
