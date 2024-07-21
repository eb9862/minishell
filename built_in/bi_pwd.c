/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:48:38 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/20 23:34:40 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <linux/limits.h> // linux PATH_MAX
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdio.h>

#include "built_in.h"

// PATH_MAX는 널문자를 포함한 길이인가?
int	pwd(void)
{
	char	path[PATH_MAX + 1];
	size_t	l;

	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("getcwd() cannot execute\n");
		return (1);
	}
	l = ft_strlen(path);
	path[l] = '\n';
	path[l + 1] = '\0';
	write(1, &path, l + 1);
	return (0);
}
