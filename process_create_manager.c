/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_create_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:00:08 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 17:03:43 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_process_list	*create_process_list(void)
{
	t_process_list	*process_list;

	process_list = (t_process_list *)malloc(sizeof(t_process_list));
	if (!process_list)
		return (0);
	process_list -> head = NULL;
	process_list -> tail = NULL;
	process_list -> count = 0;
	return (process_list);
}

t_process_info	*create_process_info(void)
{
	t_process_info	*process_info;

	process_info = (t_process_info *)malloc(sizeof(t_process_info));
	if (!process_info)
		return (0);
	process_info -> program_name = NULL;
	process_info -> argv = NULL;
	process_info -> is_redirected = 0;
	process_info -> in = STDIN_FILENO;
	process_info -> out = STDOUT_FILENO;
	process_info -> infile_name = NULL;
	process_info -> outfile_name = NULL;
	process_info -> next = NULL;
	return (process_info);
}

void    set_fd(t_process_info *process, t_q_token *target, t_q_token_list *list)
{
    t_q_token   *now;

    now = list -> head;
    while (now -> next != target)
        now = now -> next;
    if (now -> type == RDRT_AO || now -> type == RDRT_TO)
        process -> out = target -> fd;
    if (now -> type == RDRT_IN || now -> type == RDRT_HD)
        process -> in = target -> fd; 
}





int	regist_process(t_process_list *process_list, t_q_token *st, \
	t_q_token *et, t_q_token_list *token_list)
{
	t_process_info	*process_info;
	t_q_token			*now;
	int				cc;

	cc = get_plain_count(token_list);
	process_info = create_process_info();
	if (!process_info)
		return (0);
	now = st;
	while (now != et)
	{
		if (now -> type == FILE_C || now -> type == DELI)
		    set_fd(process_info, now, token_list);
		if (now -> type == RDRT_AO || now -> type == RDRT_HD \
			|| now -> type == RDRT_TO || now -> type == RDRT_IN)
			process_info -> is_redirected = 1;
		now = now -> next;
	}
	if (!set_cmd(process_info, st, et, cc))
    {
        clear_pl_tl(token_list,process_list );
        return (0);
    }
    add_process_last(process_list, process_info);
	return (1);
}

t_process_list	*get_process_list(t_q_token_list *token_list)
{
	t_process_list      *process_list;
	t_q_token			*s_token;
	t_q_token			*e_token;

	s_token = token_list -> head;
	e_token = token_list -> head;
	process_list = create_process_list();
	if (!process_list)
	{
		clear_q_token_list(token_list);
		return (0);
	}
	while (e_token)
	{
		while (e_token && e_token -> type != PIP)
			e_token = e_token -> next;
		if (!regist_process(process_list, s_token, e_token, token_list))
			return (0);
		if (e_token)
		{
			s_token = e_token -> next;
			e_token = e_token -> next;
		}
	}
	return (process_list);
}
