/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 21:31:21 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_line(char *line, char **envp, int *status)
{
	// t_token_list	*token_list;
	// t_process_list	*process_list;
	char			*expand_line;

	(void) envp;
	(void) status;
	if (!check_quotes_syntax(line))
	{
		printf("syntax error : quotes error!!!!!!!\n");
		return ;
	}
	expand_line =  get_expand_line(line);
	(void) expand_line;
	// token_list = get_token_list(line);
	// if (!token_list)
	// 	return ;
	// if (!validate(token_list))
	// 	return ;
	// process_list = get_process_list(token_list);
	// if (!process_list)
	// {
	// 	clear_token_list(token_list);
	// 	return ;
	// }
	// handle_process(process_list, envp, status, process_list -> count);
	// clear_process_list(process_list);
	// clear_token_list(token_list);
}
