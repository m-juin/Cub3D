/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:38:20 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/19 11:47:46 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	**ft_arrjoin(char **arr, char *to_join)
{
	int		i;
	char	**joined;

	i = 0;
	if (arr == NULL)
	{
		joined = malloc(sizeof(char *) * 2);
		joined[0] = ft_strdup(to_join);
		joined[1] = NULL;
		return (joined);
	}
	while (arr[i] != NULL)
		i++;
	joined = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr[i] != NULL)
	{
		joined[i] = ft_strdup(arr[i]);
		i++;
	}
	joined[i] = ft_strdup(to_join);
	joined[i + 1] = NULL;
	ft_freearr(arr);
	return (joined);
}
