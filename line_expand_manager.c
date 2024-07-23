/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:47:46 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 22:25:25 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	token -> content_len = ft_strlen(token -> content);
	token -> next = NULL;
	token -> type = get_type(token -> content[0]);
	token -> fd = -1;
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
		list -> tail = now;
	}
}

int    register_q_token(t_q_token_list *list, char *line, int s, int e)
{
	t_q_token	*token;
	int			dollar_sign_idx;

	token = create_q_token(line, s, e);
	if (!token)
		return (0);
	dollar_sign_idx = get_dollar_sign_idx(token -> content);
	if (token -> type == PLAIN && dollar_sign_idx != -1)
		token -> content = get_expanded_content(token -> content, dollar_sign_idx);
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
        if(!register_q_token(list, line, s, e))
		{
			clear_q_token_list(list);
			return (0);
		}
        s = ++e;
    }
    return (1);
}

t_q_token_list    *get_expand_line(char *line)
{
    t_q_token_list  *list;

    list = create_q_token_list();
    if (!list)
        return (0);
    if (!fill_q_token(list, line))
		return (0);
	if (!expand_double_quotes(list))
		return (0);
	if (!handle_single_quotes(list))
		return (0);
	delete_space(list);
	// if (validate_token_list(list))
	// 	return (0);
	if (!expand_redirection(list))
		return (0);
	return (list);
}
