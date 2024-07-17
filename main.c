/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/17 21:01:01 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status;

int	quotes_check(char *line)
{
	int	sq_count;
	int	dq_count;
	int	i;

	i = 0;
	sq_count = 0;
	dq_count = 0;
	while(line[i])
	{
		if (line[i] == '\'')
			sq_count++;
		if (line[i] == '\"')
			dq_count++;
		i++;
	}
	if (sq_count % 2 != 0 || dq_count % 2 != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env(envp);
	(void)env_list;
	while (1)
	{
		line = readline("porschell🏎  ");
		if (!quotes_check(line))
		{
			printf("syntax error : check quotes\n");
			continue ;
		}
		if (!line)
			break ;
		add_history(line);
		handle_line(line, envp, &status);
		free(line);
	}
}
