/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/17 15:36:31 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_line(char *line, char **envp)
{
	t_token_list	*token_list;
	t_process_list	*process_list;

	token_list = get_token_list(line);
	if (!token_list)
		return ;
	if (!validate(token_list))
		return ;
	process_list = get_process_list(token_list);
	if (!process_list)
	{
		clear_token_list(token_list);
		return ;
	}
	handle_process(process_list, envp);
	clear_process_list(process_list);
	clear_token_list(token_list);
}
