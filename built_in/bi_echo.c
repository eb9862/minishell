/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:45:30 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 16:33:15 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "built_in.h"

static int	is_option_n(char *s)
{
	int	i;

	if (s[0] != '-')
		return (-1);
	i = 1;
	while (*(s + i) != '\0')
	{
		if (*(s + i) != 'n')
			return (-1);
		i++;
	}
	if (i == 1)
		return (-1);
	else
		return (0);
}

static int	check_continuous_option_n(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_option_n(argv[i]) != 0)
			return (i);
		i++;
	}
	return (i);
}

static char	*concat_argv(int argc, char **argv)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	tmp1 = malloc(sizeof(char) * 1);
	*tmp1 = '\0';
	i = check_continuous_option_n(argv);
	while (i < argc)
	{
		tmp2 = ft_strjoin(tmp1, argv[i]);
		free(tmp1);
		tmp1 = ft_strdup(tmp2);
		free(tmp2);
		if (i != argc - 1)
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	return (tmp1);
}

void	echo(int argc, char *argv[])
{
	char	*res;
	char	*tmp;
	int		option_n;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	option_n = is_option_n(argv[1]);
	tmp = concat_argv(argc, argv);
	if (option_n != 0)
	{
		res = ft_strcat(tmp, '\n');
		free(tmp);
		write(1, res, ft_strlen(res));
		free(res);
	}
	else
	{
		write(1, tmp, ft_strlen(tmp));
		free(tmp);
	}
}
