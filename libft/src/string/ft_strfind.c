/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:26:30 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 10:47:21 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strfind(char *str, char *searched)
{
	unsigned int	pos;
	unsigned int	spos;

	pos = 0;
	while (str[pos] != '\0')
	{
		spos = 0;
		while (searched[spos] && searched[spos] == str[pos + spos])
			spos++;
		if (searched[spos] == '\0')
			return (pos);
		pos++;
	}
	return (-1);
}
