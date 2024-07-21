/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:06:04 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/21 18:00:22 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_dollar_sign_idx(char *line)
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

char	*get_expanded_content(char *content, int dollar_idx)
{
	char	*env_str;
	char	*new_conetnt;
	int		env_len;
	int		idx;
	int		env_idx;

	idx = -1;
	env_idx = -1;
	printf("str = %s\n",content + dollar_idx + 1 );
	env_str = getenv(content + dollar_idx + 1);
	printf("env_str = %s\n", env_str);
	env_len = get_env_len(env_str);
	new_conetnt = (char *)malloc(sizeof(char) * (dollar_idx + env_len + 1));
	if (!new_conetnt)
		return (0);
	while (++idx < dollar_idx)
		new_conetnt[idx] = content[idx];
	while (env_str[++env_idx])
		new_conetnt[++idx + env_idx] = env_str[env_idx];
	new_conetnt[idx + env_idx] = 0;
	free(content);
	return (new_conetnt);
}

int expand_content(t_q_token *token)
{
    int		dollar_idx;

    dollar_idx = get_dollar_sign_idx(token -> content);
    if (dollar_idx != -1)
	{
		token -> content = get_expanded_content(token -> content, dollar_idx);
		if (!token -> content)
			return (0);
		change_double2single(token -> content);
	}
	else
		change_double2single(token -> content);
	printf("new content = %s\n", token -> content);
	return (1);
}

int	expand_double_quotes(t_q_token_list *list)
{
	t_q_token	*now;

	now = list -> head;
	while (now)
	{
		if (now -> type == DOUBLE_QOUTES)
		{
			if(!expand_content(now))
                return (0);
		}
        now = now -> next;
	}
    return (1);
}