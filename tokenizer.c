/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:03:46 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 01:23:13 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token_type is_seperator(char *s)
{
    if (ft_strncmp(s, "|", 1) == 0)
        return (PIPE);
    if (ft_strncmp(s, ">>", 2) == 0)
        return (RDRT_APPEND_OUT);
    if (ft_strncmp(s, "<<", 2) == 0)
        return (RDRT_HEREDOC);
    if (ft_strncmp(s, ">", 1) == 0)
        return (RDRT_TRUNC_OUT);
    if (ft_strncmp(s, "<", 1) == 0)
        return (RDRT_INPUT);
    return (CMD);
}
void adjust_file_name(t_token_list *token_list)
{
    t_token *token;

    token = token_list -> head;
    while(token)
    {
        if (token -> previous)
        {
            if (token -> previous -> type == RDRT_APPEND_OUT)
                token -> type = FILE_CONTENT;
            if (token -> previous -> type == RDRT_INPUT)
                token -> type = FILE_CONTENT;
            if (token -> previous -> type == RDRT_TRUNC_OUT)
                token -> type = FILE_CONTENT;
            if (token -> previous -> type == RDRT_HEREDOC)
                token -> type = DELEMETER;
        }
        token = token -> next;
    }
}

int fill_token(t_token_list *token_list, char *line)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (line[i])
    {
        while(line[i] && !is_seperator(line + i))
            i++;
        if(!regist_token(token_list, line, j, i))
            return(0);
        j = i;
        while(line[i] && is_seperator(line + i))
            i++;
        if(!regist_token(token_list, line, j, i))
            return(0);
        j = i;
    }
    return (1);
}

t_token_list *create_token_list()
{
    t_token_list *token_list;

    token_list = (t_token_list *)malloc(sizeof(t_token_list));
    if (!token_list)
        return (0);
    token_list -> head = NULL;
    token_list -> tail = NULL;
    return (token_list);
}

t_token_list *get_token_list(char *line)
{
    t_token_list *token_list;
    
    token_list = create_token_list();
    if (!token_list)
        return (0);
    if(!fill_token(token_list, line))
        return (0);
    adjust_file_name(token_list);
    if (!handle_file(token_list))
        return (0);
    return (token_list);
}
