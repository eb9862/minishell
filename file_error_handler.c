/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:33:05 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/25 13:41:30 by eunhwang         ###   ########.fr       */
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
