/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:12:44 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/22 14:13:28 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_update_doors(t_door **door_list, t_data *data)
{
	int	pos;

	if (door_list[0]->anim_count == 0)
		return ;
	pos = 0;
	while (door_list[pos] != NULL)
	{
		door_list[pos]->speed_count++;
		if (door_list[pos]->speed_count >= door_list[pos]->anim_speed)
		{
			door_list[pos]->speed_count = 0;
			if (door_list[pos]->anim_state + 1 > door_list[pos]->anim_count)
				door_list[pos]->anim_state = 0;
			else
				door_list[pos]->anim_state++;
			ft_draw_ray3d(data);
		}
		pos++;
	}
}

t_door	*ft_get_door(t_ivector map_pos, t_door **doors)
{
	size_t	pos;

	pos = 0;
	while (doors != NULL && doors[pos] != NULL)
	{
		if (doors[pos]->map_pos.x == map_pos.x
			&& doors[pos]->map_pos.y == map_pos.y)
		{
			return (doors[pos]);
		}
		pos++;
	}
	return (NULL);
}
