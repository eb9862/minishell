/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:23:05 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/17 14:18:59 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd(t_process_info *process, t_token *st, t_token *et, int cmd_count)
{
	char	**argv;
	t_token	*now;
	int		i;

	i = 0;
	now = st;
	argv = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!argv)
		return (0);
	while (now != et)
	{
		if (now -> type == CMD)
			argv[i++] = now -> content;
		now = now -> next;
	}
	argv[i] = 0;
	process -> program_name = argv[0];
	process -> argv = argv;
	return (1);
}

int	set_file_content(t_process_info *process, \
	t_token *token, t_token_list *token_list)
{
	t_token	*now;
	int		res;

	now = token_list -> head;
	while (now && now != token)
		now = now -> next;
	res = open_file(process, now);
	if (res == -1)
	{
		printf("%s", token -> content);
		printf(": create file error");
		return (0);
	}
	else if (res == -2)
	{
		printf("%s", token -> content);
		printf(": No such file or directory\n");
		return (0);
	}
	return (1);
}

int	set_heredoc_fd(t_process_info *process, t_token *token)
{
	process -> in = token -> fd;
	return (1);
}

void	add_process_last(t_process_list *list, t_process_info *process)
{
	t_process_info	*now;

	if (!list -> head)
	{
		list -> head = process;
		list -> tail = process;
	}
	else
	{
		now = list -> head;
		while (now -> next)
			now = now -> next;
		now -> next = process;
	}
	list -> count++;
}

int	set_str_data(t_process_info *process, \
	t_token *token, t_token_list *token_list)
{
	if (token -> type == FILE_CONTENT)
	{
		if (!set_file_content(process, token, token_list))
			return (0);
	}
	else if (token -> type == DELEMETER)
	{
		if (!set_heredoc_fd(process, token))
			return (0);
	}	
	return (1);
}
