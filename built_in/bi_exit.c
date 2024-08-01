/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:49:45 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/02 02:24:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "built_in.h"

int	bi_exit(int argc, char *argv[])
{
	if (argc == 1)
		exit(0);
	if (argc >= 2)
	{
		if (is_numeric(argv[1]) != 0 || is_ll(argv[1]) != 0)
		{
			write(2, "bash: exit: ", 13);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 28);
		}
		else
		{
			if (argc > 2)
			{
				write(2, "bash: exit: too many arguments\n", 31);
				write(1, "not exit\n", 9);
				return (1);
			}
		}
		exit(1);
	}
	return (0);
}
