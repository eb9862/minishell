/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:34:33 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 16:51:27 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delemeter(char *line, char *delemeter)
{
	if (ft_strlen(delemeter) != ft_strlen(line) - 1)
		return (0);
	if (ft_strncmp(delemeter, line, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

int	create_heredoc_file(char *delemeter)
{
	int		fd;
	char	*line;

	fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (is_delemeter(line, delemeter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (1);
}

int	create_child_process_4_heredoc(char *delemeter)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_heredoc_signal();
		if (!create_heredoc_file(delemeter))
			exit(1);
		else
			exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (g_status >> 8 == 130)
			return (0);
		return (1);
	}
}

int	handle_heredoc(t_q_token_list *list, t_q_token *now)
{
	char	*delemeter;
	int		fd;

	delemeter = now -> content;
	if (!create_child_process_4_heredoc(delemeter))
	{
		clear_q_token_list(list);
		return (0);
	}
	fd = open("tmp_file", O_RDONLY);
	if (fd == -1)
	{
		clear_q_token_list(list);
		return (0);
	}
	now -> fd = fd;
	return (1);
}
