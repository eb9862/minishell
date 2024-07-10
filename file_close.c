/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:57:47 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/10 22:03:56 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_file(t_token_list *token_list)
{
	t_token *token;

	token = token_list -> head;
	while(token)
	{
		if (token -> type == FILE_CONTENT || \
			token -> type == DELEMETER)
			close(token -> fd);
		token = token -> next;
	}
}
