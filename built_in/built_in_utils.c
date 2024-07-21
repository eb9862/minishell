/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:53:58 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/21 00:05:50 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "built_in.h"

char	*ft_strcat(char *s, char c)
{
	size_t	i;
	size_t	l;
	char	*res;

	l = ft_strlen(s);
	res = malloc(sizeof(char) * (l + 2));
	i = 0;
	while (i < l)
	{
		*(res + i) = *(s + i);
		i++;
	}
	*(res + i++) = c;
	*(res + i) = '\0';
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL)
		return (*s2);
	if (s2 == NULL)
		return (*s1);
	while (*(s1 + i) != '\0' && *(s2 + i) != '\0')
	{
		if (*(s1 + i) != *(s2 + i))
			break ;
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}

static void	swap_str(t_env_node *node1, t_env_node *node2)
{
	char	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

void	environ_sort(t_env_node *lst)
{
	t_env_node	*tmp1;
	t_env_node	*tmp2;

	tmp1 = lst;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp1->content, tmp2->content) > 0)
			{
				swap_str(tmp1, tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	free_2d(char **s)
{
	int	n;

	n = 0;
	while (*(s + n) != 0)
	{
		free(*(s + n));
		n++;
	}
	free(s);
}
