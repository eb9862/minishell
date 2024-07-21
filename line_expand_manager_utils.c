/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expand_manager_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:02:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/21 16:34:47 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_q_token_list  *create_q_token_list()
{
    t_q_token_list  *list;

    list = (t_q_token_list *)malloc(sizeof(t_q_token_list));
    if (!list)
        return (0);
    list -> head = NULL;
    list -> tail = NULL;
    return (list);
}

int get_type(char c)
{
    if (c == '\'')
        return (SINGLE_QUOTES);
    if (c == '\"')
        return (DOUBLE_QOUTES);
    if (c == ' ')
        return (SPACE_TYPE);
    return (PLAIN);
}

int get_next_same_type_element_idx(char *line, int idx)
{
    int type;

    type = get_type(line[idx++]);
    if (type == PLAIN || type == SPACE_TYPE)
    {
        while (line[idx] && get_type(line[idx]) == type)
            idx++;
        return (idx - 1);
    }
    else
    {
        while (line[idx] && get_type(line[idx]) != type)
            idx++;
        return (idx);
    }
}