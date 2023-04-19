/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:27:39 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/19 12:00:44 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_addstr(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		x;

	x = 0;
	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[x])
	{
		join[i] = s2[x];
		x++;
		i++;
	}
	join[i] = '\0';
	if (s1)
		free(s1);
	return (join);
}
