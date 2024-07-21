/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:58:07 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/16 16:45:05 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "built_in.h"

// env, export 둘 다 key만 존재하는 환경변수는 못 불러오는 듯??
// 내 함수가 문제일 가능성 높음
void	env(t_env_list *lst)
{
	size_t		l;
	t_env_node	*tmp;

	tmp = lst -> head;
	while (tmp)
	{
		if (include_equal(tmp -> content) != -1)
		{
			l = ft_strlen(tmp -> content);
			write(1, tmp->content, l);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
// 비교 시에 마지막 환경변수 차이 _=./test | _=/usr/bin/env
