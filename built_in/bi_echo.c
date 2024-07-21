/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:45:30 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/21 00:08:16 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "built_in.h"

void	echo(int argc, char *argv[])
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	if (argc == 1) // 문자열 없이 -n 옵션만 올 경우 "\n" 출력x
	{
		write(1, "\n", 1);
		return ;
	}
	tmp1 = malloc(sizeof(char) * 1);
	*tmp1 = '\0';
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '$') // argv[i]가 $~로 들어온 환경변수라면 env()로 변환 후 join 해야함
			tmp2 = ft_strjoin(tmp1, argv[i]);
		else
		{
			argv[i]++;
			tmp2 = ft_strjoin(tmp1, getenv(argv[i]));
		}
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
	// if -n 옵션
	tmp2 = ft_strcat(tmp1, '\n');
	free(tmp1);
	write(1, tmp2, ft_strlen(tmp2));
	free(tmp2);
}
