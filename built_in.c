/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:25:16 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/16 19:51:53 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
 #include <linux/limits.h> // linux PATH_MAX
//#include <sys/syslimits.h>
#include <stdio.h>
#include <stdlib.h>

#include "built_in.h"
#include "minishell.h"

void	echo(int argc, char *argv[])
{
	int	i;
	char	*tmp1;
	char	*tmp2;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	tmp1 = malloc(sizeof(char) * 1);
	*tmp1 = '\0';
	i = 1;
	while (i < argc)
	{
		// argv[i]가 $~로 들어온 환경변수라면 env()로 변환 후 join 해야함
		if (argv[i][0] != '$')
			tmp2 = ft_strjoin(tmp1, argv[i]);
		else
		{
			argv[i]++;
			tmp2 = ft_strjoin(tmp1, getenv(argv[i]));
		}
		free(tmp1);
		tmp1 = ft_strdup(tmp2);
		free(tmp2);
		if (i != argc - 1)
		{
			tmp2 = ft_strjoin(tmp1, " ");
			free(tmp1);
			tmp1 = ft_strdup(tmp2);
			free(tmp2);
		}
		i++;
	}
	// if -n 옵션
	tmp2 = ft_strcat(tmp1, '\n');
	free(tmp1);
	write(1, tmp2, ft_strlen(tmp2));
	free(tmp2);
}

int	cd(char *path)
{
	//그냥 cd => path 없으면 home으로
	if (*path == '\0')
		path = getenv("HOME");  // getenv 반환이 null일 경우?

	if (chdir(path) != 0) // 디렉토리 변경 성공 시 0, 실패시 -1 반환
	{
		perror("Fail to change directory\n");
		return (1);
	}
	return (0);
}

int	pwd(void)
{
	size_t	l;
	char	path[PATH_MAX + 1];  // PATH_MAX는 널문자를 포함한 길이인가?

	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("getcwd() cannot execute\n");
		return (1);
	}
	l = ft_strlen(path);
	path[l] = '\n';
	path[l + 1] = '\0';
	write(1, &path, l + 1);
	return (0);
}

void	export(int argc, t_env_node *head)
{
	char	**res;
	t_env_list	*tmp_lst;
	t_env_node	*lst;

	// 매개변수 없이 export 실행시 declare -x {key}="{value}"
	if (argc != 1)
	{
		// 정렬 후 출력해야함? -> env는 정렬되지않고 나오기 때문에 정렬하면 안됨..
		// 복사 후 정렬
		tmp_lst = copy_env_list(head);
		lst = tmp_lst->head;
		environ_sort(lst);
		while (lst)
		{
			res = ft_split(lst->content, '=');
			write(1, "declare -x ", 11);
			write(1, res[0], ft_strlen(res[0]));
			if (*(res[1]) != '\0')
			{
				write(1, "=", 1);
				write(1, "\"", 1);
				write(1, res[1], ft_strlen(res[1]));
				write(1, "\"\n", 2);
			}
			lst = lst->next;
		}
		// export와 비교 시 차이
		// {declare -x _="./test"} 추가로 출력됨
	}
	/*else // 매개변수 존재하는 케이스
	{
		
	}*/
}

void	unset(int argc, char *argv[], t_env_list *lst)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		del_env_node(lst, argv[i]);
		i++;
	}
}
// env / export 둘 다 key만 존재하는 환경변수는 envp에서 못 불러오는 듯??
// >> 내 함수 문제일 가능성이 큼
void	env(t_env_node *lst)
{
	size_t	l;
	t_env_node	*tmp;

	tmp = lst;
	while (tmp)
	{
		l = ft_strlen(tmp->content);
		write(1, tmp->content, l);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	// 비교 시에 마지막 환경변수 차이 _=./test | _=/usr/bin/env
}

/*int	built_in_exit(int argc)
{
	write(1, "exit\n", 5);
	if (argc > 2)
	{
		perror("too many arguments");
		return (1);
	}
	return (0);
}*/

// int	main(int argc, char *argv[], char *envp[])
// {
// 	printf("test : %d %s\n", argc, argv[0]);
// 	t_env_list *test = init_env(envp);
	
// 	t_env_node *head = test->head;
// 	export(argc, head);
// 	unset(argc, argv, test);
// 	write(1, "#################################################\n",50);
// 	export(argc, head);
// 	//env(head);
// 	clear_env_list(test);
// }
