/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:05:15 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/19 12:08:33 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_foreach(char **arr, void (*f)(char *))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		f(arr[i]);
		i++;
	}
}
