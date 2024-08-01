/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:30:16 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/01 16:51:47 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_in_process(int sig)
{
	printf("\n");
	(void) sig;
}

void	sigquit_in_process(int sig)
{
	write(2, "Quit (core dumped)\n", 19);
	(void) sig;
}

void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
	(void) sig;
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
