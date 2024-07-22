/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:37:57 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 10:44:50 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_left_redirection(t_q_token *now)
{
	char	*content;

	content = now -> content;
	if (ft_strlen(content) == 1)
		now -> type = RDRT_IN;
	else if (ft_strlen(content) == 2)
		now -> type = RDRT_HD;
	else
		now -> type = RDRT_ERR;
}

void	handle_right_redirection(t_q_token *now)
{
	char	*content;

	content = now -> content;
	if (ft_strlen(content) == 1)
		now -> type = RDRT_TO;
	else if (ft_strlen(content) == 2)
		now -> type = RDRT_AO;
	else
		now -> type = RDRT_ERR;
}

void	set_rdrt(t_q_token_list *list)
{
	t_q_token *now;

    now = list -> head;
    while (now)
    {
        if (now -> type == RDRT_L)
		{
            handle_left_redirection(now);
			if (now -> next && now -> next -> type == PLAIN)
				now -> next -> type = FILE_C;
		}
        if (now -> type == RDRT_R)
		{
            handle_right_redirection(now);
			if (now -> next && now -> next -> type == PLAIN)
				now -> next -> type = FILE_C;
			if (now -> next && now -> next -> type == PLAIN && \
				now -> type == RDRT_HD )
				now -> next -> type = FILE_C;
		}
        now = now -> next;
    }
}

int expand_redirection(t_q_token_list *list)
{
	set_rdrt(list);
	if (!validate_token_list(list))
		return (0);
	// if (!open_files(list))
	// 	return (0);
	return (1);
}