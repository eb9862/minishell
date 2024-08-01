/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 15:20:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status = 0;

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	status = 0;
	env_list = init_env(envp);
	set_signal(); // test
	while (1)
	{
		line = readline("porschell🏎  ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		add_history(line);
		handle_line(line, envp, env_list);
		free(line);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	clear_env_list(env_list, 0);
}
