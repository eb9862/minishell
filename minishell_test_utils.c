/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:36:12 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/23 17:39:18 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_argv(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("argv[%d] = %s\n", i, s[i]);
		i++;
	}
}

void	print_process(t_process_info *process)
{
	printf("====process====\n");
	printf("name = %s\n", process -> program_name);
	print_argv(process -> argv);
	printf("in = %d\n", process -> in);
	printf("infile_name = %s\n", process -> infile_name);
	printf("is_redirected = %d\n", process -> is_redirected);
	printf("out = %d\n", process -> out);
	printf("outfile_name = %s\n", process -> outfile_name);
}


void	print_process_list(t_process_list *process_list)
{
	t_process_info	*process;

	process = process_list -> head;
	while (process)
	{
		print_process(process);
		process = process -> next;
	}
}

void print_q_token_type(int type)
{
	if (type == 0)
		printf("type = PLAIN\n");
	if (type == 1)
		printf("type = SPACE\n");
	if (type == 2)
		printf("type = SINGLE QUOTES\n");
	if (type ==3)
		printf("type = DOUBLE QUOTES\n");
	if (type ==RDRT_L)
		printf("type = RDRT LEFT\n");
	if (type ==RDRT_R)
		printf("type = RDRT RIGHT\n");
	if (type ==RDRT_TO)
		printf("type = RDRT TRUNC OUT\n");
	if (type ==RDRT_AO)
		printf("type = RDRT APPEND_OUT\n");
	if (type ==RDRT_IN)
		printf("type = RDRT IN\n");
	if (type ==RDRT_HD)
		printf("type = RDRT HD\n");
	if (type == RDRT_ERR)
		printf("type = RDRT ERR\n");
	if (type == PIP)
		printf("type = PIPE\n");
	if (type == DELI)
		printf("type = DELEMTER\n");
	if (type == FILE_C)
		printf("type = FILE\n");

}

void print_q_token(t_q_token_list *list)
{
	t_q_token *now;

	now = list -> head;
	while(now)
	{
		printf("===q_token===\n");
		printf("content %s\n", now -> content);
		printf("len = %d\n", now -> content_len);
		printf("fd = %d\n", now -> fd);
		print_q_token_type(now -> type);
		now = now -> next;
	}
}
