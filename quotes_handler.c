/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:28:20 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 17:56:20 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	check_quotes_syntax(char *line)
{
	int	i;
	int	q_flag;
	int	is_valid;

	i = 0;
	is_valid = 1;
	while (line[i])
	{
		while (line[i] && !is_quotes(line[i]))
			i++;
		q_flag = is_quotes(line[i++]);
		while (line[i] && (is_quotes(line[i]) != q_flag))
			i++;
		if (is_quotes(line[i]) == q_flag)
		{
			q_flag = 0;
			i++;
		}
		else
		{
			is_valid = 0;
			break ;
		}
	}
	return (is_valid);
}
