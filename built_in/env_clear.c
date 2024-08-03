/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:34 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 16:49:34 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

// 이게 다른데 쓰이나..?
void	clear_env_list_no_op(t_env_list *list)
{
	t_env_node	*now;
	t_env_node	*tmp;

	now = list -> head;
	while (now)
	{
		tmp = now -> next;
		free(now);
		now = tmp;
	}
	free(list);
}

void	clear_env_node(t_env_node *node)
{
	free(node -> content);
	free(node);
}
