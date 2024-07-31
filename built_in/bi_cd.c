/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:47:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/31 22:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h> // linux PATH_MAX
//#include <sys/syslimits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "built_in.h"

int	cd(int argc, char **p_argv, t_env_list *el)
{
	char	*path;

	if (argc > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	path = malloc(sizeof(char) * PATH_MAX);
	if (!path)
		return (1);
	if (argc == 2)
		path = p_argv[1];
	else
		path = getenv("HOME");
	if (chdir(path) != 0) // 디렉토리 변경 성공 시 0, 실패시 -1 반환
	{
		perror("Fail to change directory\n");
		free(path);
		return (1);
	}
	// free(path);
	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	change_value(el, "PWD", path);
	return (0);
}
