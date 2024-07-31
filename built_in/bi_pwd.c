/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:48:38 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/31 21:48:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h> // linux PATH_MAX
//#include <sys/syslimits.h>
#include <unistd.h>
#include <stdio.h>

#include "built_in.h"

// PATH_MAX는 널문자를 포함한 길이인가?
int	pwd(t_env_list *el)
{
	/*char	path[PATH_MAX + 1];
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
	return (0);*/
	t_env_node	*tmp;
	char		**key_value;

	tmp = find_node(el, "PWD");
	key_value = env_split(tmp -> content);
	printf("%s\n", key_value[1]);
	free_2d(key_value);
	return (0);
}
