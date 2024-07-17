/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:44:12 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/17 20:12:23 by joojeon          ###   ########.fr       */
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

// evnp -> linked list
typedef struct s_env_node
{
	char				*content;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
}	t_env_list;

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

t_env_list			*init_env(char **envp);
void				clear_env_list(t_env_list *env_list);
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
void				handle_process(t_process_list *process_list, char **envp, int *status);
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
// test
void				print_process(t_process_info *process);
void				print_token_type(enum e_token_type type);
void				print_token(t_token_list *token_list);

#endif
