/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:54 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 01:21:35 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *line;
    t_env_list *env_list;

    env_list = init_env(envp);
    // t_env_node *now = env_list -> head;
    
    while(1)
    {
        line = readline("porschell🏎  ");
        if (!line)
            return (0);
        handle_line(line);
        free(line);
    }
    clear_env_list(env_list);
}
