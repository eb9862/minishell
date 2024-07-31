/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:59:53 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/31 18:30:38 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "built_in.h"

t_env_list	*copy_env_list(t_env_node *head)
{
	t_env_list	*env_list;
	t_env_node	*env_node;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	env_list -> head = NULL;
	env_list -> tail = NULL;
	while (head)
	{
		env_node = create_env_node(head -> content, head -> modified);
		if (!env_node)
		{
			clear_env_list(env_list, 1);
			return (0);
		}
		add_node_last(env_list, env_node);
		head = head->next;
	}
	return (env_list);
}

t_env_node	*find_node(t_env_list *lst, char *target_key)
{
	t_env_node	*tmp_node;
	char		**s;

	tmp_node = lst -> head;
	while (tmp_node)
	{
		s = ft_split(tmp_node -> content, '=');
		if (ft_strcmp(s[0], target_key) == 0)
		{
			free_2d(s);
			return (tmp_node);
		}
		free_2d(s);
		tmp_node = tmp_node -> next;
	}
	return (tmp_node);
}

int	include_equal(char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**env_split(char *content)
{
	size_t	l;
	int		eq;
	char	**res;

	l = ft_strlen(content);
	eq = include_equal(content);
	res = (char **) malloc(sizeof(char *) * 3);
	if (eq != -1)
	{
		*res = ft_substr(content, 0, eq);
		*(res + 1) = ft_substr(content, eq + 1, l - eq);
	}
	else
	{
		*res = ft_strdup(content);
		*(res + 1) = 0;
	}
	*(res + 2) = 0;
	return (res);
}

int	is_in_envp(t_env_list *lst, char *key)
{
	t_env_node	*tmp_node;
	char		**envv;

	tmp_node = lst -> head;
	while (tmp_node)
	{
		envv = env_split(tmp_node -> content);
		if (ft_strcmp(envv[0], key) == 0)
		{
			free_2d(envv);
			return (0);
		}
		free_2d(envv);
		tmp_node = tmp_node -> next;
	}
	return (1);
}
