/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:07:16 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/30 17:24:57 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "built_in.h"

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (*s != '-' && !(*(s + i) >= '0' && *(s + i) <= '9'))
		return (-1);
	i++;
	while (*(s + i) != '\0')
	{
		if (!(*(s + i) >= '0' && *(s + i) <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

// long long 범위 -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
int	is_ll(char *s)
{
	if (is_numeric(s) == -1)
		return (-1);
	else
	{
		if (s[0] != '-')
		{
			if (ft_strlen(s) > 19)
				return (-1);
			if (ft_strlen(s) == 19 && ft_strcmp(s, "9223372036854775807") > 0)
				return (-1);
		}
		else
		{
			if (ft_strlen(s) > 20)
				return (-1);
			if (ft_strlen(s) == 20 && ft_strcmp(s, "-9223372036854775808") > 0)
				return (-1);
		}
		return (0);
	}
}

int	count_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
