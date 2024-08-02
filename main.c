/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/02 22:09:46 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	write_exit_message(void)
{
	printf("exit\n");
}

void	excute_err_msg(int ac, char **av)
{
	(void) av;
	(void) ac;
	write(2, "prochell doesn't need any arguments!!\n", \
		get_content_len("prochell doesn't need any arguments!!\n"));
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;

	if (ac != 1)
	{
		excute_err_msg(ac, av);
		return (0);
	}
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
	clear_env_list(env_list);
}
