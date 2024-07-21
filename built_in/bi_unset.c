/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:52:52 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/15 19:08:44 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	unset(int argc, char *argv[], t_env_list *lst)
{
	int			i;
	t_env_node	*tmp_node;

	i = 1;
	while (i < argc)
	{
		tmp_node = find_node(lst, argv[i]);
		if (tmp_node != NULL)
			del_env_node(lst, tmp_node);
		i++;
	}
}
