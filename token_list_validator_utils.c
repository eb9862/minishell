/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_validator_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:26:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 10:45:28 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_rdrt_err(t_q_token *token)
{
    char *content;

    content = token -> content;
    if (token -> content_len == 3)
        printf("porschell: syntax error near unexpected token `>'\n");
    else
        printf("porschell: syntax error near unexpected token `>>'\n");
}

void	handle_missed_file_error()
{
	printf("porschell: syntax error near unexpected token `newline'\n");
}

void	handle_pipe_error()
{
	printf("porschell: syntax error near unexpected token `|'\n");
}

