/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:57:03 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 16:55:47 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delemeter(char *line, char *delemeter)
{
	if (ft_strncmp(delemeter, line, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

int	open_input_file(t_process_info *process, t_token *token)
{
	int	fd;

	process -> infile_name = token -> content;
	fd = open(process -> infile_name, O_RDONLY);
	if (fd == -1)
		return (-2);
	process -> in = fd;
	token -> fd = fd;
	return (1);
}

int open_file(t_process_info *process, t_token *token)
{
	enum	e_token_type type;
	int		fd;

	type = token -> previous -> type;
	if (type == RDRT_APPEND_OUT || type == RDRT_TRUNC_OUT)
	{
		process -> outfile_name = token -> content;
		if (type == RDRT_APPEND_OUT)
			fd = open(process -> outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd = open(process -> outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			return (-1);
		process -> out = fd;
		token -> fd = fd;
	}
	else if (type == RDRT_INPUT)
		return open_input_file(process, token);
	return (1);
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
				clear_token_list(token_list);
				return (0);
			}
		}
		token = token -> next;
	}
	return (1);
}
