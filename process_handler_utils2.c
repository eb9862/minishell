/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:29:07 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 22:29:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_res_path(char *path, char *p_name, char **paths)
{
	int		size;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = get_content_len(path) + get_content_len(p_name) + 1;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		free_split(paths);
		return (0);
	}
	while (path[j])
		res[i++] = path[j++];
	res[i++] = '/';
	j = 0;
	while (p_name[j])
		res[i++] = p_name[j++];
	res[i] = 0;
	return (res);
}

char	*get_path_name(char *p_name)
{
	char	**paths;
	int		i;
	char	*tmp_path;

	i = 0;
	paths = get_paths();
	if (!paths)
		return (0);
	while (paths[i])
	{
		tmp_path = get_res_path(paths[i], p_name, paths);
		if (!tmp_path)
			return (0);
		if (access(tmp_path, F_OK) == 0 && access(tmp_path, X_OK) == 0)
		{
			free_split(paths);
			return (tmp_path);
		}
		free(tmp_path);
		i++;
	}
	free_split(paths);
	if (access(p_name, F_OK) == 0 && access(p_name, X_OK) == 0)
		return (p_name);
	(handle_not_found_pg_or_directory(p_name), exit(127));
}
