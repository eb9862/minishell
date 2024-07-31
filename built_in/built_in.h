/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:37:47 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/31 18:21:43 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/libft.h"
# include <stdlib.h>

// evnp -> linked list
typedef struct s_env_node
{
	char				*content;
	struct s_env_node	*next;
	int					modified;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
}	t_env_list;

int			cd(int argc, char **p_argv, t_env_list *el);
int			pwd(t_env_list *el);
int			bi_exit(int argc, char *argv[]);
void		echo(int argc, char *argv[]);
void		env(t_env_list *lst);
void		export(int argc, t_env_list *lst, char **argv);
void		unset(int argc, char *argv[], t_env_list *lst);

char		*ft_strcat(char *s, char c);
void		environ_sort(t_env_node *lst);
void		free_2d(char **s);
int			ft_strcmp(char *s1, char *s2);
int			is_numeric(char *s);
int			is_ll(char *s);
int			count_argc(char **argv);

void		clear_env_list(t_env_list *env_list, int copied);
void		add_node_last(t_env_list *env_list, t_env_node *node);
void		del_env_node(t_env_list *list, t_env_node *target_node);
int			include_equal(char *s);
int			is_in_envp(t_env_list *lst, char *key);
char		**env_split(char *content);

int			include_plus(char *s);
void		change_value(t_env_list *lst, char *key, char *value);
void		join_value(t_env_list *lst, char *key, char *value);
int			validate_key(char *key);
void		not_valid_identifier(char *s);
void		clear_env_list_no_op(t_env_list *env_list);

t_env_list	*init_env(char **envp);
t_env_list	*copy_env_list(t_env_node *head);
t_env_node	*create_env_node(char *content, int modi);
t_env_node	*find_node(t_env_list *lst, char *target_key);

#endif
