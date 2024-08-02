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

int	is_directory(char *p_name)
{
	DIR	*dir;

	dir = opendir(p_name);
	if (dir)
	{
		is_directory_msg(p_name);
		closedir(dir);
		exit(126);
		return (1);
	}
	return (0);
}

int	has_only_dot(char *p_name)
{
	int	i;
	int	len;

	i = 0;
	len = get_content_len(p_name);
	while (i < len)
	{
		if (p_name[i] != '.')
			return (0);
		i++;
	}
	if (len == 1)
	{
		single_dot_err_msg(p_name);
		exit(2);
	}
	if (len > 1)
	{
		not_found_programe_msg(p_name);
		exit(127);
	}
	return (1);
}

char	*get_path_name(char *p_name)
{
	char	**paths;
	int		i;
	char	*tmp_path;

	i = -1;
	if (has_only_dot(p_name) || is_directory(p_name))
		return (0);
	paths = get_paths();
	if (!paths)
		return (0);
	while (paths[++i])
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
	}
	free_split(paths);
	if (access(p_name, F_OK) == 0 && access(p_name, X_OK) == 0)
		return (p_name);
	(handle_not_found_pg_or_directory(p_name), exit(127));
}
