/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:47:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/31 02:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "built_in.h"

int	cd(int argc, char **p_argv)
{
	char	*path;

	if (argc > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (p_argv[1] == (void *)0) //그냥 cd => path 없으면 home으로
		path = getenv("HOME"); // getenv 반환이 null일 경우?
	else
		path = p_argv[1];
	if (chdir(path) != 0) // 디렉토리 변경 성공 시 0, 실패시 -1 반환
	{
		perror("Fail to change directory\n");
		return (1);
	}
	return (0);
}
