/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:23:05 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/07 03:39:30 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_cmd(t_process_info *process, t_token *token)
{
    char    **argv;

    argv = ft_split(token -> content, ' ');
    if (!argv)
        return (0);
    process -> program_name = argv[0];
    process -> argv = argv;
    return (1);
}

int set_file_content(t_process_info *process, t_token *token, t_token_list *token_list)
{
    t_token *now;
    t_token *prev;

    now = token_list -> head;
    prev = NULL;
    while (now && now != token)
    {
        prev = now;
        now = now -> next;
    } 
    if (prev -> type == RDRT_APPEND_OUT || prev -> type == RDRT_TRUNC_OUT)
        process -> outfile_name = token -> content;
    if (prev -> type == RDRT_INPUT)
        process -> infile_name = token -> content;
    return (1);
}

int set_delemeter(t_process_info *process, t_token *token, t_token_list *token_list)
{
    process -> delemeter = token -> content;
    return (1);
}

void add_process_last(t_process_list *list, t_process_info *process)
{
    t_process_info *now;

    if (!list -> head)
    {
        list -> head = process;
        list -> tail = process;
    }
    else
    {
        now = list -> head;
        while(now -> next)
            now = now -> next;
        now -> next = process;
    }
}

int set_str_data(t_process_info *process ,t_token *token, t_token_list *token_list)
{
    if (token -> type == CMD)
    {
        if (!set_cmd(process, token))
            return (0);
    }
    else if (token -> type == FILE_CONTENT)
    {
        if (!set_file_content(process, token, token_list))
            return (0);
    }
    else if (token -> type == DELEMETER)
    {
        if (!set_delemeter(process, token, token_list))
            return (0);
    }

    return (1);
}
