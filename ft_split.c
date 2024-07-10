/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:45:26 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/03 17:42:35 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_word_count(char const *s, char c)
{
	int	status;
	int	word_count;
	int	idx;

	idx = 0;
	status = 0;
	word_count = 0;
	while (s[idx])
	{
		if (s[idx] == c)
		{
			status = 0;
		}
		else
		{
			if (status == 0)
				word_count++;
			status = 1;
		}
		idx++;
	}
	return (word_count);
}

static void	clear(char **split, int s_idx)
{
	int	i;

	i = 0;
	while (i < s_idx)
	{
		free(split[i]);
		i++;
	}
}

static int	set_word(const char *s, char c, char **split, int s_idx)
{
	int		i;
	char	*mem;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	mem = (char *)malloc((i + 1) * sizeof(char));
	if (!mem)
	{
		clear(split, s_idx);
		return (0);
	}
	i = 0;
	while (s[i] && s[i] != c)
	{
		mem[i] = s[i];
		i++;
	}
	mem[i] = 0;
	split[s_idx] = mem;
	return (1);
}

char	**ft_split(char const *s, char c)
{	
	int		i;
	int		s_idx;
	char	**split;

	if (!s)
		return (0);
	i = 0;
	s_idx = 0;
	split = (char **)malloc((get_word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (!set_word(s + i, c, split, s_idx++))
				return (0);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	split[s_idx] = 0;
	return (split);
}