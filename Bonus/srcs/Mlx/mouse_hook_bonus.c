/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:00:28 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/22 16:07:40 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    cursor_hook(double x, double y, void *param)
{
    t_data	*data;

	data = (t_data *)param;
	if (x > WIDTH / 2)
	{
		data->cursor->side = west;
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
		data->player->player_angle = fix_ang(data->player->player_angle - 1);
		ft_draw_ray_minimap(data);
	}
	else if (x < WIDTH / 2)
	{
		data->cursor->side = east;
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
		data->player->player_angle = fix_ang(data->player->player_angle + 1);
		ft_draw_ray_minimap(data);	
	}
}

void	rotation_hook(mlx_key_data_t keydata, t_player *pl)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (pl->facing_dir > 0)
			pl->target_dir -= 1;
		else
			pl->target_dir = 3;
		pl->canmove = false;
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (pl->facing_dir < 3)
			pl->target_dir += 1;
		else
			pl->target_dir = 0;
		pl->canmove = false;
	}
}
