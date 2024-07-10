/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:22:01 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/04 21:11:38 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*
    e_type : "각 토큰이 어떤 의미를 가지는지를 나타내는 구조체"
    CMD = 0, // EX) ls
    OPTION, // EX ) -al
    FILE_CONTENT ,
    PIPE, // |
    STD_OUT_REDI_TRUNC, // >
    STD_OUT_REDI_APPEND, // >>
    STD_IN_REDI, // <
    HEREDOC_REDI // <<
    //todo
    "(", ")"
    ' '
    "${}"
    "$?"
*/
enum e_type
{
    CMD = 0,
    OPTION,
    FILE_CONTENT,
    PIPE,
    STD_OUT_REDI_TRUNC,
    STD_OUT_REDI_APPEND,
    STD_IN_REDI,
    HEREDOC_REDI
};
/*
    t_token : 의미 단위로 쪼개어진 토큰을 의미하는 사용자 정의 타입
    char *content;     // 담기는 문자열
    enum e_type type;  // 어떤 의미를 가지는지
    int prioity;       // 가중치 -> 추후 파싱단계에서 사용
    s_token *next;     // 다음 토큰
}   t_token;
*/
typedef struct s_token
{
    char *content;
    enum e_type type;
    int prioity;
    struct s_token *next;
}   t_token;
/*
    t_token_list : 토큰을 담고있는 linked list
    t_token *head;    // 맨 처음 토큰을 바라보는 포인터
    t_token *tail;    // 맨 끝 토큰을 바라보는 포인터
*/
typedef struct s_token_list
{
    t_token *head;
    t_token *tail;
}   t_token_list;
typedef struct s_env_node
{
    char            *content;
    struct s_env_node   *next;
}   t_env_node;
typedef struct s_env_list
{
    t_env_node *head;
    t_env_node *tail;
}   t_env_list;

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

t_token_list *create_token_list();
//char    **ft_split(char const *s, char c);
t_token_list *tokenize(char *command_line);
// evnp -> linked list
t_env_list *init_env(char **envp);
void clear_env_list(t_env_list *env_list);
t_env_list	*copy_env_list(t_env_node *head);
void	del_env_node(t_env_list *list, char *env_var);

#endif
