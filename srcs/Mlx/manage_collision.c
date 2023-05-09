/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:28:53 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/08 16:37:56 by mjuin            ###   ########.fr       */
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
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
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
		&& data->map[(int)pl->map_pos.y - 1][(int)pl->map_pos.x] != '1')
		pos.y -= 1;
	else if (pl->facing_dir == west
		&& data->map[(int)pl->map_pos.y + 1][(int)pl->map_pos.x] != '1')
		pos.y += 1;
	return (pos);
}


t_dvector	collide(t_player *player, t_data *data, mlx_key_data_t keydata)
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