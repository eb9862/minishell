/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler_utils_3.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:54:36 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/04 15:55:46 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_only_dollar_sign(void)
{
	char	*dollar_sign;

	dollar_sign = malloc(sizeof(char) * 2);
	dollar_sign[0] = '$';
	dollar_sign[1] = '\0';
	return (dollar_sign);
}
