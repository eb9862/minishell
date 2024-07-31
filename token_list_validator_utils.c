/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_validator_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:26:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/31 15:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_rdrt_err(char *content)

{
	write(2, "porschell: syntax error near unexpected token ", \
		get_content_len( "porschell: syntax error near unexpected token "));
	write(2, content, get_content_len(content));
	write(2, "\n", 1);
}

void	handle_missed_file_error(void)
{
	write(2, "porschell: syntax error near unexpected token `newline'\n", \
		get_content_len("porschell: syntax error near unexpected token `newline'\n"));
	write(2, "\n", 1);
}

void	handle_pipe_error(void)
{
	printf("porschell: syntax error near unexpected token `|'\n");
}
