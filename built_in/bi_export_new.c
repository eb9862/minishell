/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:59:17 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/01 19:24:32 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "built_in.h"

static void	export_no_arg(t_env_list *lst)
{
	char		**res;
	t_env_list	*tmp_lst;
	t_env_node	*tmp_node;

	tmp_lst = copy_env_list(lst -> head);
	tmp_node = tmp_lst -> head;
	environ_sort(tmp_node);
	while (tmp_node)
	{
		res = env_split(tmp_node -> content);
		write(1, "declare -x ", 11);
		write(1, res[0], ft_strlen(res[0]));
		if (*(res + 1) != (void *)0 || include_equal(tmp_node -> content) != -1)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, res[1], ft_strlen(res[1]));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		free_2d(res);
		tmp_node = tmp_node -> next;
	}
	clear_env_list(tmp_lst, 1);
}

static void	plus_equal(t_env_list *lst, char *arg, int eq, int plus)
{
	char	*key;
	char	*value;
	char	*key_eq;

	key = ft_substr(arg, 0, plus);
	value = ft_substr(arg, eq + 1, ft_strlen(arg) - eq + 1);
	if (is_in_envp(lst, key) == 0)
		join_value(lst, key, value);
	else
	{
		key_eq = ft_strjoin(key, "=");
		add_node_last(lst, create_env_node(ft_strjoin(key_eq, value), 1));
		free(key_eq);
	}
	free(key);
	free(value);
}

static void	equal_in_arg(t_env_list *lst, char *arg, int eq)
{
	int		plus;
	char	**key_value;

	plus = include_plus(arg);
	if (plus == -1)
	{
		key_value = env_split(arg);
		if (validate_key(key_value[0]) == -1)
			not_valid_identifier(arg);
		else if (is_in_envp(lst, key_value[0]) == 0)
			change_value(lst, key_value[0], key_value[1]);
		else
			add_node_last(lst, create_env_node(arg, 0));
		free_2d(key_value);
	}
	else
	{
		if (eq == 0 || plus == 0 || plus < eq - 1)
			not_valid_identifier(arg);
		else if (plus == eq - 1)
			plus_equal(lst, arg, eq, plus);
		else
			add_node_last(lst, create_env_node(arg, 0));
	}
}

static void	export_with_arg(t_env_list *lst, int argc, char **argv)
{
	int		i;
	int		eq;

	i = 1;
	while (i < argc)
	{
		eq = include_equal(argv[i]);
		if (eq == -1)
		{
			if (validate_key(argv[i]) == -1)
				not_valid_identifier(argv[i]);
			else if (is_in_envp(lst, argv[i]) != 0)
				add_node_last(lst, create_env_node(argv[i], 0));
				// 지금은 마지막에 추가했는데 env로 확인해보면 마지막에 들아가는게 아닌거 같음 // 무슨 순서???
			// else 같은 key의 환경변수가 이미 존재하면 아무 변화없음
		}
		else
			equal_in_arg(lst, argv[i], eq);
		i++;
	}
}

void	export(int argc, t_env_list *lst, char **argv)
{
	if (argc == 1)
		export_no_arg(lst);
	// 새로운 환경변수를 추가하게 되면 env 명령어 결과의 순서가 어떻게 ???
	else
		export_with_arg(lst, argc, argv);
}

// = 있음 -> 첫번째 = 뒤로 다 value값으로 처리, += 가능, -= 안됨
// bash: export: `e-=world': not a valid identifier
// bash: export: `=': not a valid identifier
// bash: export: `b++': not a valid identifier
