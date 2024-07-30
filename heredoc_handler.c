/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:34:33 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 20:36:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delemeter(char *line, char *delemeter)
{
	if (ft_strlen(delemeter) != ft_strlen(line))
		return (0);
	if (ft_strncmp(delemeter, line, ft_strlen(line)) == 0)
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
		line = readline("> ");
		if (is_delemeter(line, delemeter))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (1);
}

int	create_child_process_4_heredoc(char *delemeter, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!create_heredoc_file(delemeter))
			exit(1);
		else
			exit(0);
	}
	else
	{
		waitpid(pid, status, 0);
		if (*status == 1)
			return (0);
		return (1);
	}
}


int	handle_heredoc_v2(t_q_token_list *list, t_q_token *now, int *status)
{
	char	*delemeter;
	int		fd;
	
	delemeter = now -> content;
	if (!create_child_process_4_heredoc(delemeter, status))
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
