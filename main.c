/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 22:43:47 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env(envp);
	while (1)
	{
		line = readline("porschell🏎  ");
		if (!line)
			return (0);
		handle_line(line);
		free(line);
	}
	clear_env_list(env_list);
}
