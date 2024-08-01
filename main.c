/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 16:32:33 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	write_exit_message(void)
{
	printf("\nexit\n");
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
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	clear_env_list(env_list, 0);
}
