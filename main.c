/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 21:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	write_exit_message(void)
{
	printf("exit\n");
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	g_status = 0;
	env_list = init_env(envp);
	set_signal();
	while (1)
	{
		line = readline("porschell🏎  ");
		if (!line)
		{
			write_exit_message();
			break ;
		}
		add_history(line);
		handle_line(line, envp, env_list);
		free(line);
	}
	clear_env_list(env_list, 0);
}
