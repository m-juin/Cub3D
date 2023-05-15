/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:06:05 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/15 15:36:17 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	ft_check_pos(t_data *data, int state)
{
	if (state == 1)
	{
		if ((float)data->player->map_pos.x != (float)data->player->target_pos.x \
		|| (float)data->player->map_pos.y != (float)data->player->target_pos.y)
			return (true);
		return (false);
	}
	if (state == 2)
	{
		if ((float)data->player->map_pos.x == (float)data->player->target_pos.x \
		&& (float)data->player->map_pos.y == (float)data->player->target_pos.y)
			return (true);
		return (false);
	}
	return (false);
}

bool	ft_move(t_data *data)
{
	if (data->player->canmove == false && ft_check_pos(data, 1) == true)
	{
		if (data->player->map_pos.x < data->player->target_pos.x)
			data->player->map_pos.x += 0.05;
		else if (data->player->map_pos.x > data->player->target_pos.x)
			data->player->map_pos.x -= 0.05;
		if (data->player->map_pos.y > data->player->target_pos.y)
			data->player->map_pos.y -= 0.05;
		else if (data->player->map_pos.y < data->player->target_pos.y)
			data->player->map_pos.y += 0.05;
		data->player->minimap_pos.x = data->player->map_pos.x * MAP_CSIZE;
		data->player->minimap_pos.y = data->player->map_pos.y * MAP_CSIZE;
		data->player->minimap_offset.x = data->player->player_center.x - data->player->minimap_pos.x;
		data->player->minimap_offset.y = data->player->player_center.y - data->player->minimap_pos.y;
		ft_draw_ray_minimap(data);
		ft_draw_ray3d(data);
		if (ft_check_pos(data, 2) == true)
			return (true);
		else
			return (false);
	}
	return (true);
}
