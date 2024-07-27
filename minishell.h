/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:44:12 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/27 15:31:50 by joojeon          ###   ########.fr       */
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
void				handle_line(char *line, char**envp, int *status);
void				handle_process(t_process_list *process_list, \
						char **envp, int *status, pid_t *pids);
char				**ft_split(char const *s, char c);
void				clear_process_list(t_process_list *list);
void				add_process_last(t_process_list *list, \
						t_process_info *process);
char				*get_next_line(int fd);
void				free_split(char **split);
int					check_quotes_syntax(char *line);
t_q_token_list		*get_expand_line(char *line, int *status);
int					get_type(char c);
t_q_token_list		*create_q_token_list(void);
int					get_next_same_type_element_idx(char *line, int idx);
int					expand_double_quotes(t_q_token_list *list, int *status);
int					get_dollar_sign_idx(char *line);
void				change_double2single(char *s);
int					get_env_len(char *env);
char				*get_only_env(char *s);
char				*get_new_content(char *content, int dollar_idx, char *env);
char				*get_new_content_ds(char *content, int dollar_idx, char *env);
char				*get_q_content(char *line, int s, int e);
t_q_token			*create_q_token(char *line, int s, int e);
void				clear_q_token_list(t_q_token_list *list);
int					handle_single_quotes(t_q_token_list *list);
void				clear_q_token(t_q_token *token);
int					expand_redirection(t_q_token_list *list, int *status);
void				delete_space(t_q_token_list *list);
int					validate_token_list(t_q_token_list *list);
void				handle_rdrt_err(t_q_token *token);
void				handle_missed_file_error(void);
void				handle_pipe_error(void);
void				handle_file_open_error(char *content);
void				handle_file_create_error(char *content);
int					get_content_len(char *s);
int					open_files(t_q_token_list *list, int *status);
int					trim_each_token_quotes(t_q_token_list *list);
void				clear_process(t_process_info *process);
t_process_list		*get_process_list(t_q_token_list *token_list);
int					handle_heredoc_v2(t_q_token_list *list, t_q_token *now, int *status);
void				clear_pl_tl(t_q_token_list *token_list, t_process_list *process_list);
int					get_plain_count(t_q_token_list *list);
void				add_process_last(t_process_list *list, t_process_info *process);
int					set_cmd(t_process_info *process, t_q_token *st, t_q_token *et, int cmd_count);
int					get_dollar_sign_idx(char *line);
char				*get_expanded_content(char *content, int dollar_idx, int *status);
int					expand_plain(t_q_token_list *list, int *status);
// test
void				print_process(t_process_info *process);
void				print_process_list(t_process_list *process_list);
void				print_q_token(t_q_token_list *list);
// test too
void	sigint_in_process(int sig);
void	sigquit_in_process(int sig);
void	sigint_handler(int sig);
void	set_signal(void);

#endif
