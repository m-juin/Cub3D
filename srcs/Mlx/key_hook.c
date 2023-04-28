/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/28 11:12:10 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	t_ivector offset;
	if (player->angle >= 0 && player->angle < 180)
		offset.y = -5;
	else
		offset.y = 5;
	if ((player->angle >= 270 && player->angle < 360) || (player->angle >= 0 && player->angle < 90))
		offset.x = 5;
	else
		offset.x = -5;
	int	ipx = player->pos.x / 64.0;
	int	ipx_add_xo = (player->pos.x + offset.x) / 64.0;
	int	ipx_sub_xo = (player->pos.x - offset.x) / 64.0;
	int	ipy = player->pos.y / 64.0;
	int	ipy_add_yo = (player->pos.y + offset.y) / 64.0;
	int	ipy_sub_yo = (player->pos.y - offset.y) / 64.0;
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{	
		if (data->map[ipy][ipx_add_xo] != '1')
		{
			player->pos.x += player->delta.x * 2;
		}
		if (data->map[ipy_add_yo][ipx] != '1')
		{
			player->pos.y += player->delta.y * 2;
		}
		ft_draw_ray3d(data);
	}	
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (data->map[ipy][ipx_sub_xo] != '1')
		{
			player->pos.x -= player->delta.x * 2;
		}
		if (data->map[ipy_sub_yo][ipx] != '1')
		{
			player->pos.y -= player->delta.y * 2;
		}
		ft_draw_ray3d(data);
	}	
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
	}	
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
	}
	player->img->instances[0].x = player->pos.x;
	player->img->instances[0].y = player->pos.y;
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *player, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->angle = fix_ang(player->angle + 5);
		player->delta.x = cos(deg_to_rad(player->angle));
		player->delta.y = -sin(deg_to_rad(player->angle));
		ft_draw_ray3d(data);
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->angle = fix_ang(player->angle - 5);
		player->delta.x = cos(deg_to_rad(player->angle));
		player->delta.y = -sin(deg_to_rad(player->angle));
		ft_draw_ray3d(data);
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
	movement_hook(keydata, ((t_data *)param)->player, (t_data *)param);
	rotation_hook(keydata, ((t_data *)param)->player, (t_data *)param);
	close_hook(keydata);
}
