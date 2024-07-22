/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:44:12 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 20:44:21 by joojeon          ###   ########.fr       */
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

enum e_token_type
{
	CMD = 0,
	PIPE,
	RDRT_APPEND_OUT,
	RDRT_HEREDOC,
	RDRT_TRUNC_OUT,
	RDRT_INPUT,
	FILE_CONTENT,
	DELEMETER
};

// token
typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	int					fd;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

//process_info
typedef struct s_process_info
{
	char					*program_name;
	char					**argv;
	int						in;
	int						out;
	char					*infile_name;
	char					*outfile_name;
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
enum e_token_type	is_seperator(char *s);
int					regist_token(t_token_list *token_list, \
						char *line, int start, int end);
void				clear_token_list(t_token_list *token_list);
t_token_list		*get_token_list(char *line);
void				handle_line(char *line, char**envp, int *status);
int					validate(t_token_list *token_list);
int					is_redirection(enum e_token_type type);
void				redirection_newline_error(void);
void				redirection_chaining_error(enum e_token_type type);
void				pipe_error(void);
t_process_list		*get_process_list(t_token_list *token_list);
void				handle_process(t_process_list *process_list, char **envp, \
						int *status, int count);
void				adjust_file_name(t_token_list *token_list);
char				**ft_split(char const *s, char c);
void				clear_process_list(t_process_list *list);
int					set_str_data(t_process_info *process, \
						t_token *token, t_token_list *token_list);
void				add_process_last(t_process_list *list, \
						t_process_info *process);
void				excute(t_process_list *process_list);
char				*get_next_line(int fd);
void				free_split(char **split);
int					create_heredoc_file(t_token *token);
int					handle_file(t_token_list *token_list);
int					open_file(t_process_info *process, t_token *token);
int					set_cmd(t_process_info *process, t_token *st, \
						t_token *et, int cmd_count);
int					check_quotes_syntax(char *line);
char				*get_expand_line(char *line);
int					get_type(char c);
t_q_token_list 		*create_q_token_list();
int					get_next_same_type_element_idx(char *line, int idx);
int					expand_double_quotes(t_q_token_list *list);
int					get_dollar_sign_idx(char *line);
void				change_double2single(char *s);
int					get_env_len(char *env);
char				*get_only_env(char *s);
char				*get_new_content(char *content, int dollar_idx, char *env);
char				*get_q_content(char *line, int s, int e);
t_q_token			*create_q_token(char *line, int s, int e);
void				clear_q_token_list(t_q_token_list *list);
int					handle_single_quotes(t_q_token_list *list);
void				clear_q_token(t_q_token *token);
int					expand_redirection(t_q_token_list *list);
void				delete_space(t_q_token_list *list);
int					validate_token_list(t_q_token_list *list);
void   				handle_rdrt_err(t_q_token *token);
void				handle_missed_file_error();
void				handle_pipe_error();
void				handle_file_open_error(char *content);
void				handle_file_create_error(char *content);
int					get_content_len(char *s);
int					open_files(t_q_token_list *list);
int					trim_each_token_quotes(t_q_token_list *list);
// test
void				print_process(t_process_info *process);
void				print_token_type(enum e_token_type type);
void				print_token(t_token_list *token_list);
void				print_q_token(t_q_token_list *list);


#endif
