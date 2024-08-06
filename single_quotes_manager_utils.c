/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_manager_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonwan <joonwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:07:50 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/06 15:59:25 by joonwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_content_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	trim_single_quotes(t_q_token *now)
{
	char	*new_content;
	int		size;
	int		idx;
	int		c_idx;

	idx = 0;
	c_idx = 1;
	size = get_content_len(now -> content) - 2;
	new_content = (char *)malloc(sizeof(char) * size + 1);
	if (!new_content)
		return (0);
	while (c_idx < get_content_len(now -> content) - 1)
		new_content[idx++] = now -> content[c_idx++];
	new_content[idx] = 0;
	free(now -> content);
	now -> content = new_content;
	now -> content_len = size;
	if (now -> type == SINGLE_QUOTES)
		now -> type = PLAIN;
	return (1);
}

int	trim_each_token_quotes(t_q_token_list *list)
{
	t_q_token	*now;

	now = list -> head;
	while (now)
	{
		if (now -> type == SINGLE_QUOTES)
		{
			if (!trim_single_quotes(now))
			{
				clear_q_token_list(list);
				return (0);
			}
		}
		now = now -> next;
	}
	return (1);
}

char	*combine_plain_plain(char *s1, char *s2)
{
	char	*combined_content;
	int		size;
	int		i1;
	int		s_idx;

	i1 = 1;
	s_idx = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	combined_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!combined_content)
		return (0);
	combined_content[0] = '\'';
	while (s1[s_idx])
		combined_content[i1++] = s1[s_idx++];
	s_idx = 0;
	while (s2[s_idx])
		combined_content[i1++] = s2[s_idx++];
	combined_content[i1++] = '\'';
	combined_content[i1] = 0;
	free(s1);
	return (combined_content);
}
