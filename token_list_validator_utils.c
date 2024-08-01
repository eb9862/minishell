/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_validator_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:26:38 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 16:11:58 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_rdrt_err(char *content)

{
	write(2, "porschell: syntax error near unexpected token ", \
		get_content_len("porschell: syntax error near unexpected token "));
	write(2, content, get_content_len(content));
	write(2, "\n", 1);
}

void	handle_missed_file_error(void)
{
	write(2, "porschell: syntax error near unexpected token `newline'\n", \
		get_content_len("porschell: syntax error \
			near unexpected token `newline'\n"));
	write(2, "\n", 1);
}

void	handle_pipe_error(void)
{
	printf("porschell: syntax error near unexpected token `|'\n");
}
