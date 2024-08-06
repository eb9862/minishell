/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:22:26 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 23:22:19 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_stream(int in, int out)
{
	if (in != 0)
		dup2(in, STDIN_FILENO);
	if (out != 1)
		dup2(out, 1);
}

void	save_original(int *original_in, int *original_out)
{
	*original_in = dup(STDIN_FILENO);
	*original_out = dup(STDOUT_FILENO);
}

char	**get_paths(char *p_name, t_env_list *el)
{
	char	*path_line;
	char	**split;

	path_line = get_env_value(el, "PATH", p_name);
	split = ft_split(path_line, ':');
	if (!split)
	{
		free(path_line);
		return (0);
	}
	free(path_line);
	return (split);
}

int	is_contains_slash(char *p_name)
{
	int	i;

	i = 0;
	while (p_name[i])
	{
		if (p_name[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	handle_not_found_pg_or_directory(char *p_name)
{
	if (is_contains_slash(p_name))
	{
		write(2, "porschell: ", get_content_len("porschell: "));
		write(2, p_name, get_content_len(p_name));
		write(2, ": No such file or directory\n", \
			get_content_len(": No such file or directory\n"));
	}
	else
		not_found_programe_msg(p_name);
}
