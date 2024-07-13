/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:42 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 16:01:44 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token_type(enum e_token_type type)
{
     printf("token type = ");
     if(type == CMD)
          printf("CMD");
     if(type == PIPE)
          printf("PIPE");
     if(type == RDRT_APPEND_OUT)
          printf("RDRT_APPEND_OUT");
     if(type == RDRT_HEREDOC)
          printf("RDRT_HEREDOC");
     if(type == RDRT_TRUNC_OUT)
          printf("RDRT_TRUNC_OUT");
     
     if(type == RDRT_INPUT)
          printf("RDRT_INPUT");
     if(type == FILE_CONTENT)
          printf("FILE_CONTENT");
     if(type == DELEMETER)
          printf("DELEMETER");
     printf("\n");
}
void print_argv(char **s)
{
     int i = 0;
     while(s[i])
     {
          printf("argv[%d] = %s\n", i, s[i]);
          i++;
     }
}

void print_process(t_process_info *process)
{
     printf("====process====\n");
     printf("name = %s\n", process -> program_name);
     print_argv(process -> argv);
     printf("delemeter = %s\n", process -> delemeter);
     printf("in = %d\n", process -> in);
     printf("infile_name = %s\n", process -> infile_name);
     printf("is_heredoc = %d\n", process -> is_heredoc);
     printf("is_redirected = %d\n", process -> is_redirected);
     printf("out = %d\n", process -> out);
     printf("outfile_name = %s\n", process -> outfile_name);
}

void print_token(t_token_list *token_list)
{
     t_token *token;

     token = token_list -> head;
     while(token)
     {    
          printf("===token===\n");
          print_token_type(token -> type);
          printf("content = %s\n", token -> content);
          printf("fd = %d\n", token -> fd);
          token = token -> next;
     }
}

void handle_line(char *line)
{
    t_token_list *token_list;
    t_process_list *process_list;

     token_list = get_token_list(line);
     if (!token_list)
          return ;
     if (!validate(token_list))
          return ;
     print_token(token_list);
     process_list = get_process_list(token_list);
     if (!process_list)
     {
          clear_token_list(token_list);
          return ;
     }
     excute(process_list);
     clear_process_list(process_list);
     clear_token_list(token_list);
}
