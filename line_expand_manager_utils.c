/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_manager_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:02:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/31 15:33:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_q_token_list	*create_q_token_list(void)
{
	t_q_token_list	*list;

	list = (t_q_token_list *)malloc(sizeof(t_q_token_list));
	if (!list)
		return (0);
	list -> head = NULL;
	list -> tail = NULL;
	return (list);
}

int	get_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	if (c == '\"')
		return (DOUBLE_QOUTES);
	if (c == ' ')
		return (SPACE_TYPE);
	if (c == '>')
		return (RDRT_R);
	if (c == '<')
		return (RDRT_L);
	if (c == '|')
		return (PIP);
	return (PLAIN);
}


int	get_next_same_type_element_idx(char *line, int idx)
{
	int	type;
	int	count;

	count = 0;
	type = get_type(line[idx++]);
	if (type == PLAIN || type == SPACE_TYPE || type == RDRT_L || RDRT_R || PIP)
	{
		while (line[idx] && get_type(line[idx]) == type)
		{
			count++;
			idx++;
			if (type == RDRT_L || type == RDRT_R)
			{
				if (count == 1)
					break;
			}
		}
		return (idx - 1);
	}
	else
	{
		while (line[idx] && get_type(line[idx]) != type)
			idx++;
		return (idx);
	}
}

char	*get_q_content(char *line, int s, int e)
{
	int		idx;
	int		size;
	char	*content;

	idx = 0;
	size = e - s + 1;
	content = (char *)malloc(sizeof(char) * (size + 1));
	if (!content)
		return (0);
	while (s <= e)
		content[idx++] = line[s++];
	content[idx] = 0;
	return (content);
}
