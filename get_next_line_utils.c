/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:02:56 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/09 23:08:26 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*mem;
	int		mem_idx;
	int		i;

	i = 0;
	mem_idx = 0;
	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!mem)
		return (0);
	if (s1)
	{
		while (s1[i])
			mem[mem_idx++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		mem[mem_idx++] = s2[i++];
	mem[mem_idx] = 0;
	free(s1);
	return (mem);
}

char	*get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_backup(char *backup)
{
	char	*new_backup;
	int		i;
	int		n;
	int		size;

	i = 0;
	n = 0;
	size = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	size = ft_strlen(backup) - i;
	if (size == 0)
	{
		free(backup);
		return (0);
	}
	new_backup = (char *)malloc(sizeof(char) * (size));
	if (!new_backup)
		return (0);
	i++;
	while (backup[i])
		new_backup[n++] = backup[i++];
	new_backup[n] = 0;
	free(backup);
	return (new_backup);
}
