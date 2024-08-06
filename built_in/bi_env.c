/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:58:07 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 16:34:39 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "built_in.h"

void	env(t_env_list *lst)
{
	size_t		l;
	t_env_node	*tmp;

	tmp = lst -> head;
	while (tmp)
	{
		if (include_equal(tmp -> content) != -1)
		{
			l = ft_strlen(tmp -> content);
			write(1, tmp->content, l);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
