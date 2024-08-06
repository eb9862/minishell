/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonwan <joonwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:08:22 by joonwan           #+#    #+#             */
/*   Updated: 2024/08/06 22:14:17 by joonwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_command(char *p_name)
{
	if (get_content_len(p_name) == 0)
	{
		not_found_programe_msg(p_name);
		exit(127);
	}
	return (0);
}