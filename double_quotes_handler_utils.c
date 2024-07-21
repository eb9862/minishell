/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:40:55 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 00:19:04 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_content(char *content, int dollar_idx, char *env)
{
	int		size;
	char	*new_content;
	int		c_i;
	int		e_i;

	e_i = 0;
	c_i = -1;
	size = dollar_idx + get_env_len(env) + 1;
	new_content = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_content)
	{
		free(content);
		return (0);
	}
	while (++c_i < dollar_idx)
		new_content[c_i] = content[c_i];
	while (e_i < get_env_len(env))
		new_content[c_i++] = env[e_i++];
	new_content[c_i++] = '\"';
	new_content[c_i] = 0;
	free(content);
	return (new_content);
}


char	*get_only_env(char *s)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (!res)
		return (0);
	while (s[i] && s[i] != '\"')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	get_dollar_sign_idx(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
            return (i);
        i++;
    }
    return (-1);
}

void	change_double2single(char *s)
{
	int len;

	len = ft_strlen(s);
	s[0] = '\'';
	s[len - 1] = '\'';
}

int	get_env_len(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}
