/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:08:22 by joonwan           #+#    #+#             */
/*   Updated: 2024/08/06 23:30:26 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_command(char *p_name)
{
	if (get_content_len(p_name) == 0)
	{
		not_found_programe_msg(p_name);
		exit(127);
	}
	return (0);
}

char	*get_env_value(t_env_list *el, char *env_key, char *p_name)
{
	t_env_node	*tmp_node;
	int			eq;
	int			l;
	char		*res;

	tmp_node = find_node(el, env_key);
	if (!tmp_node)
	{
		write(2, "porschell: ", get_content_len("porschell: "));
		write(2, p_name, get_content_len(p_name));
		write(2, ": No such file or directory\n", \
			get_content_len(": No such file or directory\n"));
		exit(127);
	}
	eq = include_equal(tmp_node -> content);
	l = ft_strlen(tmp_node -> content);
	if (eq != -1)
	{
		res = ft_substr(tmp_node -> content, eq + 1, l - (eq + 1));
		return (res);
	}
	else
		return (0);
}
