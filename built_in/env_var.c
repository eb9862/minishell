/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:24:21 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/30 21:56:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "built_in.h"

t_env_node	*create_env_node(char *content, int modi)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node)
		return (0);
	node -> content = content;
	node -> next = NULL;
	node -> modified = modi;
	return (node);
}

void	clear_env_list(t_env_list *env_list, int copied)
{
	t_env_node	*now;
	t_env_node	*tmp;

	now = env_list -> head;
	if (now)
	{
		while (now)
		{
			tmp = now -> next;
			if (copied == 0 && now -> modified == 1)
				free(now -> content);
			free(now);
			now = tmp;
		}
	}
	free(env_list);
}

void	add_node_last(t_env_list *env_list, t_env_node *node)
{
	t_env_node	*tmp;

	if (env_list == NULL || env_list-> head == NULL)
	{
		env_list -> head = node;
		env_list -> tail = node;
	}
	else
	{
		tmp = env_list -> head;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = node;
		env_list -> tail = node;
	}
}

t_env_list	*create_env_list()
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (0);
	env_list -> head = NULL;
	env_list -> tail = NULL;
	return (env_list);
}

t_env_list	*init_env(char **envp)
{
	int			i;
	t_env_list	*env_list;
	t_env_node	*env_node;

	i = 0;
	env_list = create_env_list();
	if (!env_list)
		return (0);
	while (envp[i])
	{
		env_node = create_env_node(envp[i], 0);
		if (!env_node)
		{
			clear_env_list(env_list, 0);
			return (0);
		}
		add_node_last(env_list, env_node);
		i++;
	}
	return (env_list);
}

void	del_env_node(t_env_list *list, t_env_node *target_node)
{
	t_env_node	*tmp_node;
	t_env_node	*next_node;

	tmp_node = list -> head;
	if (tmp_node == target_node)
	{
		list -> head = target_node -> next;
		if (target_node -> modified == 1)
			free(target_node -> content);
		free(target_node);
		return ;
	}
	next_node = tmp_node -> next;
	while (tmp_node)
	{
		if (next_node == target_node)
		{
			tmp_node -> next = next_node -> next;
			if (target_node -> modified == 1)
				free(target_node -> content);
			free(target_node);
			return ;
		}
		tmp_node = tmp_node -> next;
		next_node = tmp_node -> next;
	}
}
