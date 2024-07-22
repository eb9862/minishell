/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:34:33 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 21:55:19 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delemeter_v2(char *line, char *delemeter)
{
    printf("delemeter = %s\n", delemeter);
	if (ft_strlen(delemeter) != ft_strlen(line) - 1)
		return (0);
	if (ft_strncmp(delemeter, line, ft_strlen(line) - 1) == 0)
		return (1);
	return (0);
}

int	create_heredoc_file_v2(char *delemeter)
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
		if (!line || is_delemeter_v2(line, delemeter))
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

int handle_heredoc_v2(t_q_token_list *list,t_q_token *now)
{
    char    *delemeter;
    int     fd;

    delemeter = now -> content;
    if (!create_heredoc_file_v2(delemeter))
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