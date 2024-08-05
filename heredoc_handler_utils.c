/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:09:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/05 14:25:48 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line(char **line, int *ctrl_d)
{
	if (!(*line))
		*ctrl_d = 1;
	else
		free(*line);
}

void	print_ctrl_d_msg(char *delemeter)
{
	printf("porschell: warning: here-document at line 130 delimited");
	printf(" by end-of-file (wanted `%s')\n", delemeter);
}
