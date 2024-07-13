/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:08:40 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 23:12:13 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token -> content = NULL;
	token -> type = CMD;
	token -> next = NULL;
	token -> previous = NULL;
	token -> fd = -1;
	return (token);
}

char	*get_content(char *line, int start, int end)
{
	int		size;
	int		content_idx;
	char	*content;

	content_idx = 0;
	size = end - start + 1;
	content = (char *)malloc(sizeof(char) * size);
	if (!content)
	{
		return (0);
	}
	while (content_idx + start < end)
	{
		content[content_idx] = line[content_idx + start];
		content_idx++;
	}
	content[content_idx] = 0;
	return (content);
}

void	add_token_last(t_token_list *token_list, t_token *token)
{
	t_token	*now;

	if (!token_list || !token)
		return ;
	if (!token_list -> head)
	{
		token_list -> head = token;
		token_list -> tail = token;
	}
	else
	{
		now = token_list -> head;
		while (now -> next)
			now = now -> next;
		now -> next = token;
		token -> previous = now;
	}
}

int	is_only_white_space(char *s, int start, int end)
{
	int	idx;
	int	flag;

	flag = 1;
	idx = start;
	while (idx < end)
	{
		if (!((s[idx] >= 9 && s[idx] <= 13) || s[idx] == 32))
			flag = 0;
		idx++;
	}
	return (flag);
}

int	regist_token(t_token_list *token_list, char *line, int start, int end)
{
	t_token	*token;
	char	*content;

	if (start == end || is_only_white_space(line, start, end))
		return (1);
	token = create_token();
	if (!token)
		return (0);
	token -> type = is_seperator(line + start);
	content = get_content(line, start, end);
	if (!content)
	{
		clear_token_list(token_list);
		return (0);
	}
	token -> content = ft_strtrim(content, " 	");
	if (!token -> content)
	{
		clear_token_list(token_list);
		return (0);
	}
	add_token_last(token_list, token);
	return (1);
}
