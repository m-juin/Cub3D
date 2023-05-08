/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/08 15:07:32 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	t_dvector target;

	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *player, t_data *data)
{

	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (player->facing_dir > 0)
			player->target_dir -= 1;
		else
			player->target_dir = 3;
		player->canmove = false;
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
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
