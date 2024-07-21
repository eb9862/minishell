/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:47:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/21 00:10:36 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	cd(char *path)
{
	if (*path == '\0') //그냥 cd => path 없으면 home으로
		path = getenv("HOME"); // getenv 반환이 null일 경우?
	if (chdir(path) != 0) // 디렉토리 변경 성공 시 0, 실패시 -1 반환
	{
		perror("Fail to change directory\n");
		return (1);
	}
	return (0);
}
