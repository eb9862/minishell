/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:39:20 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/06 20:33:51 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirection_newline_error()
{
    printf("syntax error near unexpected token \'newline\'\n");
}

void redirection_chaining_error(enum e_token_type type)
{
    printf("syntax error near unexpected token ");
    if (type == PIPE)
        printf("\'|\'\n");
    if (type == RDRT_APPEND_OUT)
        printf("\'>>\'\n");
    if (type == RDRT_HEREDOC)
        printf("\'<<\'\n");
    if (type == RDRT_INPUT)
        printf("\'<\'\n");
    if (type == RDRT_TRUNC_OUT)
        printf("\'>\'\n");
}

void pipe_error()
{
    printf("syntax error near unexpected token `|'\n");
}

int is_redirection(enum e_token_type type)
{
    if(type == RDRT_APPEND_OUT)
        return (1);
    if(type == RDRT_HEREDOC)
        return (1);
    if(type == RDRT_INPUT)
        return (1);
    if(type == RDRT_TRUNC_OUT)
        return (1);
    return (0);
}