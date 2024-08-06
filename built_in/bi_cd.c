/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:47:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 20:47:36 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "built_in.h"

int	cd(int argc, char **p_argv, t_env_list *el)
{
	char	*path;

	if (argc > 2)
	{
		write(2, "porschell: cd: too many arguments\n", 34);
		return (1);
	}
	if (argc == 2)
		path = p_argv[1];
	else
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		write(2, "porschell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": ", 3);
		perror("");
		return (1);
	}
	path = getcwd(NULL, 0);
	change_value(el, "PWD", path);
	free(path);
	return (0);
}
