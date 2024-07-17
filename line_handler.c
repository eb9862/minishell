/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/17 21:20:00 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(t_token *now, int *status)
{
	free(now -> content);
	now -> content = ft_itoa(*status >> 8);
}

void	handle_envp(t_token *now)
{
	char *tmp;

	tmp = ft_strdup(getenv(now -> content + 1));
	free(now -> content);
	now -> content = tmp;
}

void	handle_dollar_sign(t_token_list *token_list, int *status)
{
	t_token *now;

	now = token_list -> head;
	while(now)
	{
		if (now -> content[0] == '$')
		{
			if (now -> content[1] && now -> content[1] == '?' && ft_strlen(now -> content) == 2)
				handle_status(now, status);
			else if(now -> content[1])
				handle_envp(now);
		}
		now = now -> next;
	}
}

void	handle_line(char *line, char **envp, int *status)
{
	t_token_list	*token_list;
	t_process_list	*process_list;

	token_list = get_token_list(line);
	if (!token_list)
		return ;
	if (!validate(token_list))
		return ;
	handle_dollar_sign(token_list, status);
	process_list = get_process_list(token_list);
	if (!process_list)
	{
		clear_token_list(token_list);
		return ;
	}
	handle_process(process_list, envp, status);
	clear_process_list(process_list);
	clear_token_list(token_list);
}
