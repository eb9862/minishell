/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:16:25 by marvin            #+#    #+#             */
/*   Updated: 2024/07/30 16:16:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void    clear_env_list_no_op(t_env_list *list)
{
    t_env_node  *now;
    t_env_node  *tmp;

    now = list  -> head;
    while (now)
    {
        tmp = now -> next;
        free(now);
        now = tmp;
    }
    free(list);
}