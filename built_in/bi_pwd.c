/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:48:38 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/01 20:42:29 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <linux/limits.h> // linux PATH_MAX
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdio.h>

#include "built_in.h"

// PATH_MAX는 널문자를 포함한 길이인가?
int	pwd(t_env_list *el)
{
	t_env_node	*tmp;
	char		**key_value;

	tmp = find_node(el, "PWD");
	key_value = env_split(tmp -> content);
	printf("%s\n", key_value[1]);
	free_2d(key_value);
	return (0);
}
