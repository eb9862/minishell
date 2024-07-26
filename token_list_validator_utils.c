/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_validator_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:26:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/25 14:54:36 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_rdrt_err(t_q_token *token)
{
	if (token -> content_len == 3)
		printf("porschell: syntax error near unexpected token `>'\n");
	else
		printf("porschell: syntax error near unexpected token `>>'\n");
}

void	handle_missed_file_error(void)
{
	printf("porschell: syntax error near unexpected token `newline'\n");
}

void	handle_pipe_error(void)
{
	printf("porschell: syntax error near unexpected token `|'\n");
}
