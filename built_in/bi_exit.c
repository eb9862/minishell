/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:49:45 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 17:32:01 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "built_in.h"

int	bi_exit(int argc, char *argv[])
{
	if (argc == 1)
		exit(0);
	if (argc == 2 && (is_numeric(argv[1]) == 0 && is_ll(argv[1]) == 0))
		exit(ft_atoi(argv[1]) % 256);
	if (argc >= 2)
	{
		if (is_numeric(argv[1]) != 0 || is_ll(argv[1]) != 0)
		{
			write(2, "porschell: exit: ", 13);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 28);
		}
		else
		{
			if (argc > 2)
			{
				write(2, "porschell: exit: too many arguments\n", 31);
				return (1);
			}
		}
		exit(1);
	}
	return (0);
}
