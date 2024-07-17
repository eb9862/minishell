/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:46:07 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/13 22:35:17 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute(t_process_list *process_list)
{
	t_process_info	*process;

	process = process_list -> head;
	while (process)
	{
		print_process(process);
		process = process -> next;
	}
}
