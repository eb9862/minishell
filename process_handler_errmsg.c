/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_errmsg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:53:37 by marvin            #+#    #+#             */
/*   Updated: 2024/08/02 16:53:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_directory_msg(char *p_name)
{
	write(2, "porschell: ", get_content_len("porschell: "));
	write(2, p_name, get_content_len(p_name));
	write(2, ": is directory\n", \
		get_content_len(": is directory\n"));
}

void	single_dot_err_msg(char *p_name)
{
	write(2, "porschell: ", get_content_len("porschell: "));
	write(2, p_name, get_content_len(p_name));
	write(2, ": filename argument required\n", \
		get_content_len(": filename argument required\n"));
	write(2, p_name, get_content_len(p_name));
	write(2, ": usage: ", get_content_len(": usage: "));
	write(2, p_name, get_content_len(p_name));
	write(2, " filename [arguments]\n", \
		get_content_len(" filename [arguments]\n"));
}

void	not_found_programe_msg(char *p_name)
{
	//write(2, "porschell: ", get_content_len("porschell: "));
	write(2, p_name, get_content_len(p_name));
	write(2, ": command not found\n", \
		get_content_len(": command not found\n"));
}
