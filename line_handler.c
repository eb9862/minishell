/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 17:38:26 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_line(char *line, char **envp, int *status)
{
	t_process_list	*process_list;
	t_q_token_list		*token_list;

	(void) envp;
	(void) status;
	if (!check_quotes_syntax(line))
	{
		printf("syntax error : quotes error!!!!!!!\n");
		return ;
	}
	token_list =  get_expand_line(line);
	if (!token_list)
		return ;
	// print_q_token(token_list);
	// if (!validate(token_list))
	// 	return ;
	process_list = get_process_list(token_list);
	if (!process_list)
		return ;
	print_process_list(process_list);
	handle_process(process_list, envp, status, process_list -> count);
	clear_process_list(process_list);
	clear_q_token_list(token_list);
}
