/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joojeon <joojeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:33:05 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/22 19:35:32 by joojeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_file_open_error(char *content)
{
	printf("porschell: %s: No such file or directory\n", content);
}

void	handle_file_create_error(char *content)
{
	printf("porschell: %s: Cannot create file\n", content);
}