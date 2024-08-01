/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:40:55 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 20:31:46 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_idx(char *content, int dollar_idx)
{
	int	idx;

	idx = dollar_idx + 1;
	while (can_env_element(content, idx, dollar_idx + 1))
		idx++;
	return (idx - 1);
}

char	*get_new_content(char *content, int dollar_idx, char *env)
{
	int		size;
	char	*new_content;
	int		ni;
	int		i;

	ni = 0;
	i = 0;
	size = get_content_len(content) - (get_end_idx(content, \
		dollar_idx) - dollar_idx + 1) + get_content_len(env);
	new_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_content)
		return (0);
	while (ni < dollar_idx)
		new_content[ni++] = content[i++];
	i = 0;
	if (env)
	{
		while (env[i])
			new_content[ni++] = env[i++];
	}
	i = get_end_idx(content, dollar_idx) + 1;
	while (content[i] && i < get_content_len(content))
		new_content[ni++] = content[i++];
	new_content[ni] = 0;
	return (new_content);
}

char	*get_new_content_ds(char *content, int dollar_idx, char *env)
{
	int		size;
	char	*new_content;
	int		ni;
	int		i;

	ni = 0;
	i = 0;
	size = get_content_len(content) - (get_end_idx(content, dollar_idx) \
		- dollar_idx + 1) + get_content_len(env);
	new_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_content)
		return (0);
	while (ni < dollar_idx)
		new_content[ni++] = content[i++];
	i = 0;
	if (env)
	{
		while (env[i])
			new_content[ni++] = env[i++];
	}
	i = get_end_idx(content, dollar_idx) + 1;
	while (content[i] && i < get_content_len(content) - 1)
		new_content[ni++] = content[i++];
	new_content[ni] = 0;
	return (new_content);
}

char	*get_only_env(char *s)
{
	int		size;
	int		i;
	char	*only_env;

	i = -1;
	size = 0;
	while (can_env_element(s, size, 0))
		size++;
	only_env = (char *)malloc(sizeof(char) * (size + 1));
	if (!only_env)
		return (0);
	while (can_env_element(s, ++i, 0))
		only_env[i] = s[i];
	only_env[i] = 0;
	return (only_env);
}

int	get_dollar_sign_idx(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}
