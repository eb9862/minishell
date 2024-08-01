/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler_utils_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:39:21 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/01 20:31:42 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

int	can_first_element(char c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	if ('A' <= c && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	can_element(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	can_env_element(char *env, int idx, int start_idx)
{
	if (idx == start_idx)
	{
		if (!can_first_element(env[idx]))
			return (0);
	}
	return (can_element(env[idx]));
}

void	change_double2single(char *s)
{
	int	len;

	len = ft_strlen(s);
	s[0] = '\'';
	s[len - 1] = '\'';
}
