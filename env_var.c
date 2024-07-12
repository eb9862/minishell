/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:24:21 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/10 21:59:49 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"

t_env_node	*create_env_node(char *content)
{
    t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node)
		return (0);
	node -> content = content;
	node -> next = NULL;
	return (node);
}

void	clear_env_list(t_env_list *env_list)
{
	t_env_node	*now;
	t_env_node	*tmp;

	now = env_list -> head;
	if (now)
	{
		while (now)
		{
			tmp = now -> next;
			free(now);
			now = tmp;
		}
	}
	free(env_list);
}

void	add_node_last(t_env_list *env_list, t_env_node *node)
{
	t_env_node	*tmp;

	if (!env_list -> head)
	{
		env_list -> head = node;
		env_list -> tail = node;
	}
	else
	{
		tmp = env_list -> head;
		while(tmp -> next)
			tmp = tmp -> next;
		tmp -> next= node;
		env_list -> tail = node;
	}
}

t_env_list	*init_env(char **envp)
{
	int			i;
	t_env_list	*env_list;
    t_env_node	*env_node;

	i = 0;
	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (0);
	while (envp[i])
	{
		env_node = create_env_node(envp[i]);
		if (!env_node)
		{
			clear_env_list(env_list);
			return (0);
		}
		add_node_last(env_list, env_node);
		i++;
	}
	return (env_list);
}
t_env_list	*copy_env_list(t_env_node *head)
{
	t_env_list	*env_list;
	t_env_node	*env_node;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	while (head)
	{
		env_node = create_env_node(head->content);
		if (!env_node)
		{
			clear_env_list(env_list);
			return (0);
		}
		add_node_last(env_list, env_node);
		head = head->next;
	}
	return (env_list);
}
#include <stdio.h>

void	del_env_node(t_env_list *list, char *env_var)
{
	t_env_node *node_1;
	t_env_node *node_2;
	char	**envir;

	node_1 = list -> head;
	node_2 = NULL;
	envir = ft_split(node_1-> content, '=');
	while (node_1 && ft_strcmp(envir[0], env_var) != 0)
	{
		free_2d(envir);
		node_2 = node_1;
		node_1 = node_1 -> next;
		if (node_1 != NULL)
			envir = ft_split(node_1-> content, '=');
	}
	// free_2d(envir);
	if (!node_1){
		return ;
	}
	if (!node_2)
		list -> head = node_1 -> next;
	else
		node_2 -> next = node_1 -> next;
	free(node_1);
}
