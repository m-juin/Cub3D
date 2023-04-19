/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:47:38 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/19 11:47:34 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**dup;
	size_t	arr_len;
	int		i;

	arr_len = ft_arrlen(arr);
	dup = malloc(sizeof(char *) * (arr_len + 1));
	if (!dup)
		return (dup);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (dup);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
