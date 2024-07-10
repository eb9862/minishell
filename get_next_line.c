/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:03:03 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/09 23:09:25 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_total_backup(int fd, char *backup)
{
	char	*buff;
	int		r_size;

	r_size = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (ft_strchr(backup, '\n') == -1 && r_size > 0)
	{
		r_size = read(fd, buff, BUFFER_SIZE);
		if (r_size == -1 || r_size == 0)
		{
			free(backup);
			free(buff);
			return (0);
		}
		buff[r_size] = 0;
		backup = ft_strjoin(backup, buff);
		if (!backup)
			return (0);
	}
	free(buff);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || 1024 < fd || BUFFER_SIZE <= 0)
		return (0);
	backup = get_total_backup(fd, backup);
	if (!backup)
		return (0);
	line = get_line(backup);
	if (!line)
	{
		free(line);
		return (0);
	}
	backup = update_backup(backup);
	return (line);
}
