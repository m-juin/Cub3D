/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:21:01 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/16 10:36:06 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_count_door(char **map)
{
	t_ivector	pos;
	int			count;

	count = 0;
	pos.y = 0;
	while (map[pos.y] != NULL)
	{
		pos.x = 0;
		while (map[pos.y][pos.x] != '\0')
		{
			if (map[pos.y][pos.x] == '2')
				count++;
			pos.x++;
		}
		pos.y++;
	}
	return (count);
}
