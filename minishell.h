/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:44:12 by joojeon           #+#    #+#             */
/*   Updated: 2024/08/01 22:37:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./built_in/built_in.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

extern int	g_status;

//process_info
typedef struct s_process_info
{
	char					*program_name;
	char					**argv;
	int						in;
	int						out;
	int						idx;
	int						is_redirected;
	struct s_process_info	*next;
}	t_process_info;

typedef struct s_process_list
{
	int				count;
	t_process_info	*head;
	t_process_info	*tail;
}	t_process_list;

enum e_q_token_type
{
	PLAIN = 0,
	SPACE_TYPE,
	SINGLE_QUOTES,
	DOUBLE_QOUTES,
	RDRT_L,
	RDRT_R,
	RDRT_AO,
	RDRT_HD,
	RDRT_TO,
	RDRT_IN,
	RDRT_ERR,
	DELI,
	PIP,
	FILE_C
};

enum e_built_in_type
{
	ECHO = 0,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct s_q_token
{
	enum e_q_token_type	type;
	char				*content;
	int					content_len;
	struct s_q_token	*next;
	int					fd;
}	t_q_token;

typedef struct s_q_token_list
{
	t_q_token	*head;
	t_q_token	*tail;
}	t_q_token_list;

//t_env_list			*init_env(char **envp);
//void				clear_env_list(t_env_list *env_list);
void				handle_line(char *line, char **envp, t_env_list *el);
void				handle_process(t_process_list *process_list, \
						char **envp, t_env_list *el, pid_t *pids);
char				**ft_split(char const *s, char c);
void				clear_process_list(t_process_list *list);
void				add_process_last(t_process_list *list, \
						t_process_info *process);
char				*get_next_line(int fd);
void				free_split(char **split);
t_q_token_list		*get_expand_line(char *line);
int					get_type(char c);
t_q_token_list		*create_q_token_list(void);
int					get_next_same_type_element_idx(char *line, int idx);
int					expand_double_quotes(t_q_token_list *list);
int					can_env_element(char *env, int idx, int start_idx);
int					get_dollar_sign_idx(char *line);
void				change_double2single(char *s);
int					get_env_len(char *env);
char				*get_only_env(char *s);
char				*get_new_content(char *content, int dollar_idx, char *env);
char				*get_new_content_ds(char *content, \
						int dollar_idx, char *env);
char				*get_q_content(char *line, int s, int e);
t_q_token			*create_q_token(char *line, int s, int e);
void				clear_q_token_list(t_q_token_list *list);
int					handle_single_quotes(t_q_token_list *list);
void				clear_q_token(t_q_token *token);
int					expand_redirection(t_q_token_list *list);
void				delete_space(t_q_token_list *list);
int					validate_token_list(t_q_token_list *list);
void				handle_rdrt_err(char *content);
void				handle_missed_file_error(void);
void				handle_pipe_error(void);
void				handle_file_open_error(char *content);
void				handle_file_create_error(char *content);
int					get_content_len(char *s);
int					open_files(t_q_token_list *list);
int					trim_each_token_quotes(t_q_token_list *list);
char				*combine_plain_plain(char *s1, char *s2);
void				clear_process(t_process_info *process);
t_process_list		*get_process_list(t_q_token_list *token_list);
int					handle_heredoc(t_q_token_list *list, t_q_token *now);
void				clear_pl_tl(t_q_token_list *token_list, \
						t_process_list *process_list);
int					get_plain_count(t_q_token_list *list);
void				add_process_last(t_process_list *list, \
						t_process_info *process);
int					set_cmd(t_process_info *process, t_q_token *st, \
						t_q_token *et, int cmd_count);
int					get_dollar_sign_idx(char *line);
char				*get_expanded_content(char *content, int dollar_idx);
int					expand_plain(t_q_token_list *list);
int					delegate_quotes_syntax_check(char *line);
void				set_rdrt(t_q_token_list *list);
void				set_file_content(t_q_token_list *list);
void				save_original(int *original_in, int *original_out);
void				handle_multiple_process(t_process_list *process_list, char **envp, \
    					pid_t *pids, t_env_list *el);
void				handle_single_built_in(t_process_info *process, t_env_list *el);
void				excute_child_process(t_process_info *process, char **envp, \
						pid_t pids[], t_env_list *el);
// 새로 구분한 파일
void				excute_built_in(t_process_info *process, \
						pid_t pids[], t_env_list *el);
void				run_built_in(t_process_info *process, t_env_list *el);
int					is_buitin(char *p_name);
int					get_argc(char **argv);
void				set_stream(int in, int out);
char				**get_paths(void);
int					is_contains_slash(char *p_name);
void				handle_not_found_pg_or_directory(char *p_name);
// test
void				print_process(t_process_info *process);
void				print_process_list(t_process_list *process_list);
void				print_q_token(t_q_token_list *list);
// test too
void				sigint_in_process(int sig);
void				sigquit_in_process(int sig);
void				sigint_handler(int sig);
void				set_signal(void);
void				set_heredoc_signal(void);
void				ignore_parent_signal();

#endif
