/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:02:52 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/06 18:08:36 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_contain(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start_idx(char  *s1, char const *set)
{
	size_t	start_idx;

	start_idx = 0;
	while (s1[start_idx] && is_contain(s1[start_idx], set))
		start_idx++;
	return (start_idx);
}

static size_t	get_end_idx(char  *s1, char const *set)
{
	size_t	end_idx;

	end_idx = ft_strlen(s1) - 1;
	while (s1[end_idx] && is_contain(s1[end_idx], set))
		end_idx--;
	return (end_idx);
}

char	*ft_strtrim(char  *s1, char const *set)
{
	size_t		start_idx;
	size_t		end_idx;
	size_t		mem_idx;
	size_t		size;
	char		*mem;

	if (!s1)
		return (0);
	mem_idx = 0;
	start_idx = get_start_idx(s1, set);
	end_idx = get_end_idx(s1, set);
	size = end_idx - start_idx + 1;
	if (start_idx == ft_strlen(s1))
		mem = (char *)malloc(sizeof(char));
	else
		mem = (char *)malloc((size + 1) * sizeof(char));
	if (!mem)
		return (0);
	while (start_idx < end_idx + 1)
		mem[mem_idx++] = s1[start_idx++];
	mem[mem_idx] = '\0';
    free(s1);
	return (mem);
}
