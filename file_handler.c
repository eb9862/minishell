/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:57:03 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 02:13:57 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delemeter(char *line, char *delemeter)
{
	if (ft_strncmp(delemeter, line, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

int	handle_heredoc(t_token *token)
{
	int		fd;
	char	*line;
	char	*delemeter;

	delemeter = token -> content;
	fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(0);
		if (!line || is_delemeter(line, delemeter)){
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	token -> fd = fd;
	return (1);
}

int	handle_file(t_token_list *token_list)
{
	t_token *token;

	token = token_list -> head;
	while(token)
	{
		if (token -> type == DELEMETER)
		{
			if (!handle_heredoc(token))
			{
				(clear_file(token_list), clear_token_list(token_list));
				return (0);
			}
		}
		token = token -> next;
	}
	return (1);
}
