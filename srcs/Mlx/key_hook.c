/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/08 10:51:20 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dvector	collide_front(t_player *pl, t_data *data)
{
	t_dvector pos;

	pos = pl->map_pos;
	if (pl->facing_dir == north
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
	else if (pl->facing_dir == south
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	else if (pl->facing_dir == east
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x + 1] != '1')
		pos.x += 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x - 1] != '1')
		pos.x -= 1;
	return (pos);
}
static t_dvector	collide_back(t_player *pl, t_data *data)
{
	t_dvector pos;

	pos = pl->map_pos;
	if (pl->facing_dir == north
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	else if (pl->facing_dir == south
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
	else if (pl->facing_dir == east
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x - 1] != '1')
		pos.x -= 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x + 1] != '1')
		pos.x += 1;
	return (pos);
}
static t_dvector	collide_right(t_player *pl, t_data *data)
{
	t_dvector pos;

	pos = pl->map_pos;
	if (pl->facing_dir == north
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x + 1] != '1')
		pos.x += 1;
	else if (pl->facing_dir == south
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x - 1] != '1')
		pos.x -= 1;
	else if (pl->facing_dir == east
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	return (pos);
}
static t_dvector	collide_left(t_player *pl, t_data *data)
{
	t_dvector pos;

	pos = pl->map_pos;
	if (pl->facing_dir == north
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x - 1] != '1')
		pos.x -= 1;
	else if (pl->facing_dir == south
		&& data->map[(int)pl->map_pos.y][(int)pl->map_pos.x + 1] != '1')
		pos.x += 1;
	else if (pl->facing_dir == east
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
	return (pos);
}

static t_dvector	collide(t_player *player, t_data *data, mlx_key_data_t keydata)
{
	t_dvector move;

	move = player->map_pos;
	if (keydata.key == MLX_KEY_W)
		move = collide_front(player, data);
	else if (keydata.key == MLX_KEY_S)
		move = collide_back(player, data);
	else if (keydata.key == MLX_KEY_D)
		move = collide_right(player, data);
	else if (keydata.key == MLX_KEY_A)
		move = collide_left(player, data);
	return (move);
}

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	t_dvector target;

	if (keydata.key == MLX_KEY_W
		&& keydata.action == MLX_RELEASE)
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_S
		&& keydata.action == MLX_RELEASE)
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		target = collide(player, data, keydata);
		if (target.x == player->map_pos.x && target.y == player->map_pos.y)
			return ;
		player->target_pos = target;
		player->canmove = false;
	}	
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
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
