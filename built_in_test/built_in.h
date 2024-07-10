/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:37:47 by eunhwang          #+#    #+#             */
/*   Updated: 2024/07/04 20:06:37 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "./libft/libft.h"

#include "minishell.h"

char	*ft_strcat(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	environ_sort(t_env_node *lst);
void	free_2d(char **s);

/*char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
*/
#endif