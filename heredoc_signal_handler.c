/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:52:16 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 14:52:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	(void) signum;
	exit(130);
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_handler); // ctrl + c
	signal(SIGQUIT, SIG_IGN); // ctrl + '\'
}