/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:38:32 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 03:03:41 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_sq_sq(char *s1, char *s2)
{
	char	*combined_content;
	int		size;
	int		i1;
	int		s_idx;

	i1 = 1;
	s_idx = 1;
	size = get_content_len(s1) + get_content_len(s2) - 2;
	combined_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!combined_content)
		return (0);
	combined_content[0] = '\'';
	while(s_idx < get_content_len(s1) - 1)
		combined_content[i1++] = s1[s_idx++];
	s_idx = 1;
	while(s_idx < get_content_len(s2) - 1)
		combined_content[i1++] = s2[s_idx++];
	combined_content[i1++] = '\'';
	combined_content[i1] = 0;
	return (combined_content); 
}

char	*combine_plain_sq(char *s1, char *s2)
{
	char	*combined_content;
	int		size;
	int		i1;
	int		s_idx;

	i1 = 1;
	s_idx = 0;
	size = get_content_len(s1) + get_content_len(s2);
	combined_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!combined_content)
		return (0);
	combined_content[0] = '\'';
	while(s1[s_idx])
		combined_content[i1++] = s1[s_idx++];
	s_idx = 1;
	while(s_idx < get_content_len(s2) - 1)
		combined_content[i1++] = s2[s_idx++];
	combined_content[i1++] = '\'';
	combined_content[i1] = 0;
	return (combined_content);
}

char	*combine_sq_plain(char *s1, char *s2)
{
	char	*combined_content;
	int		size;
	int		i1;
	int		s_idx;

	i1 = 1;
	s_idx = 1;
	size = get_content_len(s1) + get_content_len(s2);
	combined_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!combined_content)
		return (0);
	combined_content[0] = '\'';
	while(s_idx < get_content_len(s1)  - 1)
		combined_content[i1++] = s1[s_idx++];
	s_idx = 0;
	while (s2[s_idx])
		combined_content[i1++] = s2[s_idx++];
	combined_content[i1++] = '\'';
	combined_content[i1] = 0;
	return (combined_content);
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
	combined_content[i1++] = '\'';
	s_idx = 0;
	while (s2[s_idx])
		combined_content[i1++] = s2[s_idx++];
	combined_content[i1++] = '\'';
	combined_content[i1] = 0;
	return (combined_content);
}
int	combine_token(t_q_token *t1, t_q_token *t2)
{
	char	*combined_content;

	if (t1 -> type == SINGLE_QUOTES && t2 -> type == SINGLE_QUOTES)
		combined_content = combine_sq_sq(t1 -> content, t2 -> content);
	if (t1 -> type == PLAIN && t2 -> type == SINGLE_QUOTES)
		combined_content = combine_plain_sq(t1 -> content, t2 -> content);
	if (t1 -> type == SINGLE_QUOTES && t2 -> type == PLAIN)
		combined_content = combine_sq_plain(t1 -> content, t2 -> content);
	if (t1 -> type == PLAIN && t2 -> type == PLAIN)
		combined_content = combine_plain_plain(t1 -> content, t2 -> content);
	if (!combined_content)
		return (0);
	t1 -> content = combined_content;
	t1 -> next = t2 -> next;
	t1 -> content_len = ft_strlen(t1 -> content);
	t1 -> type = SINGLE_QUOTES;
	clear_q_token(t2);
	return (1);
}

int	handle_single_quotes(t_q_token_list *list)
{
	t_q_token	*now;
	t_q_token	*start;

	now = list -> head;
	start = now;
	while (now)
	{
		if (now -> next && (now -> type == SINGLE_QUOTES  || now -> type == PLAIN) && \
			(now -> next -> type == SINGLE_QUOTES || now -> next -> type == PLAIN))
		{
			if (!combine_token(now, now -> next))
			{
				clear_q_token_list(list);
				return (0); 
			}
			else
				now = start;
		}
		else
			now = now -> next;
	}
	return (1);
}
