/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:47:46 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/21 16:01:11 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_q_token *create_q_token(char *line, int s, int e)
{
	t_q_token	*token;

	token = (t_q_token *)malloc(sizeof(t_q_token));
	if (!token)
		return (0);
	token -> content = get_q_content(line, s, e);
	if (!token -> content)
	{
		free(token);
		return (0);
	}
	token -> content_len = ft_strlen(token -> content); // check out
	token -> next = NULL;
	token -> type = get_type(token -> content[0]);
	return (token);
}

void	add_q_token_last(t_q_token_list *list, t_q_token *token)
{
	t_q_token	*now;

	if (!list -> head)
	{
		list -> head = token;
		list -> tail = token;
	}
	else
	{
		now = list -> head;
		while (now -> next)
			now = now -> next;
		now -> next = token;
	}
}

int    register_q_token(t_q_token_list *list, char *line, int s, int e)
{
	t_q_token	*token;
	token = create_q_token(line, s, e);
	if (!token)
		return (0);
	add_q_token_last(list, token);
	return (1);
}


int fill_q_token(t_q_token_list *list, char *line)
{
    int s;
    int e;

    (void) list;
    s = 0;
    while (line[s])
    {
        e = get_next_same_type_element_idx(line, s);
        register_q_token(list, line, s, e);
        s = ++e;
    }
    return (1);
}

char    *get_expand_line(char *line)
{
    t_q_token_list  *list;

    list = create_q_token_list();
    if (!list)
        return (0);
    fill_q_token(list, line);
	print_q_token(list);
    return (line);
}