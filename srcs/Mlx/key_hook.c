/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/05 15:47:54 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	t_dvector offset;

	offset.x = 1;
	offset.y = 1;
	if (player->dir.x < 0)
		offset.x = -1;
	if (player->dir.y < 0)
		offset.y = -1;
	if (keydata.key == MLX_KEY_W
		&& keydata.action == MLX_RELEASE)
	{
		if (data->map[(int)player->map_pos.y][(int)(player->map_pos.x + offset.x)] != '1')
		{
			player->target_pos.x += player->dir.x;
		}
		if (data->map[(int)(player->map_pos.y + offset.y)][(int)(player->map_pos.x)] != '1')
		{
			player->target_pos.y += player->dir.y;
		}
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_S
		&& keydata.action == MLX_RELEASE)
	{
		if (data->map[(int)player->map_pos.y][(int)(player->map_pos.x - offset.x)] != '1')
		{
			player->target_pos.x -= player->dir.x;
		}
		if (data->map[(int)(player->map_pos.y - offset.y)][(int)(player->map_pos.x)] != '1')
		{
			player->target_pos.y -= player->dir.y;
		}
		player->canmove = false;
	}
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (data->map[(int)player->map_pos.y][(int)(player->map_pos.x + offset.x)] != '1')
		{
			if (player->plane.x < 0)
				player->target_pos.x += -1;
			else if (player->plane.x > 0)
				player->target_pos.x += 1;
		}
		if (data->map[(int)(player->map_pos.y + offset.y)][(int)(player->map_pos.x)] != '1')
		{
			if (player->plane.y < 0)
				player->target_pos.y += -1;
			else if (player->plane.y > 0)
				player->target_pos.y += 1;
		}
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
	}
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *player, t_data *data)
{
	double oldDirX = player->dir.x;
	double oldPlaneX = player->plane.x;

	if (keydata.key == MLX_KEY_LEFT
		&& keydata.action == MLX_RELEASE)
	{
		if (player->facing_dir > 0)
			player->target_dir -= 1;
		else
			player->target_dir = 3;
		player->canmove = false;
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& keydata.action == MLX_RELEASE)
	{
		if (player->facing_dir < 3)
			player->target_dir += 1;
		else
			player->target_dir = 0;
		player->canmove = false;
	}
}

static void	close_hook(mlx_key_data_t keydata)
{
	if (keydata.key != MLX_KEY_ESCAPE || keydata.action != MLX_RELEASE)
		return ;
	ft_exit("", 0);
}

void	handle_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (data->player->canmove == true)
	{
		movement_hook(keydata, data->player, data);
		rotation_hook(keydata, data->player, data);
	}
	close_hook(keydata);
}
