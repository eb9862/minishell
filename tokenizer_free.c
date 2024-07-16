/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:46 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/16 15:34:11 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_token *token)
{
	if (token -> type == FILE_CONTENT)
	{
		close(token -> fd);
	}
	if (token -> type == DELEMETER)
	{
		close(token -> fd);
		unlink("tmp_file");
	}
	free(token);
}

void	clear_token_list(t_token_list *token_list)
{
	t_token	*now;
	t_token	*tmp;

	now = token_list -> head;
	while (now)
	{
		tmp = now -> next;
		clear_token(now);
		now = tmp;
	}
	free(token_list);
}
