/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 16:19:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;
	int			status;

	(void)ac;
	(void)av;
	status = 0;
	env_list = init_env(envp);
	(void)env_list;
	set_signal(); // test
	while (1)
	{
		line = readline("porschell🏎  ");
		if (!line)
			break ;
		add_history(line);
		handle_line(line, envp, &status);
		free(line);
	}
	clear_env_list_no_op(env_list);
}
