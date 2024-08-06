/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:48:38 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 16:34:27 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h> // linux PATH_MAX
//#include <sys/syslimits.h>
#include <unistd.h>
#include <stdio.h>
#include "built_in.h"

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
