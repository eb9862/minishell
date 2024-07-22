/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:37:57 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 03:16:35 by joojeon          ###   ########.fr       */
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
            handle_left_redirection(now);
        if (now -> type == RDRT_R)
            handle_right_redirection(now);
        now = now -> next;
    }
}

void	set_file_content_v2(t_q_token_list *list)
{
	t_q_token *now;

	now = list -> head;
	while (now)
	{
		if (now -> next && (now -> type == RDRT_AO || now -> type == RDRT_TO || \
			now -> type == RDRT_IN))
			now -> next -> type = FILE_C;
		if (now -> next && now -> type == RDRT_HD)
			now -> next -> type = DELI;
		now = now -> next;
	}
}

int expand_redirection(t_q_token_list *list)
{
	set_rdrt(list);
	if (!trim_each_token_quotes(list))
		return (0);
	set_file_content_v2(list);
	if (!open_files(list))
		return (0);
	return (1);
}
