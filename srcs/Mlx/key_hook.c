/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/03 15:29:50 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (data->map[(int)(player->map_pos.x + player->dir.x * 5)][(int)player->map_pos.y] == false)
			player->map_pos.x += player->dir.x * 5;
		if (data->map[(int)(player->map_pos.x)][(int)(player->map_pos.y + player->dir.y * 5)] == false)
			player->map_pos.y += player->dir.y * 5;
		ft_draw_ray3d(data);
	}	
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (data->map[(int)(player->map_pos.x - player->dir.x * 5)][(int)player->map_pos.y] == false)
			player->map_pos.x -= player->dir.x * 5;
		if (data->map[(int)(player->map_pos.x)][(int)(player->map_pos.y - player->dir.y * 5)] == false)
			player->map_pos.y -= player->dir.y * 5;
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
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *player, t_data *data)
{
	double oldDirX = player->dir.x;
	double oldPlaneX = player->plane.x;

	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->dir.x = player->dir.x * cos(5) - player->dir.y * sin(5);
		player->dir.y = oldDirX * sin(5) + player->dir.y * cos(5);
		player->plane.x = player->plane.x * cos(5) - player->plane.y * sin(5);
		player->plane.y = oldPlaneX * sin(5) + player->plane.y * cos(5);
		ft_draw_ray3d(data);
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->dir.x = player->dir.x * cos(-5) - player->dir.y * sin(-5);
		player->dir.y = oldDirX * sin(-5) + player->dir.y * cos(-5);
		player->plane.x = player->plane.x * cos(-5) - player->plane.y * sin(-5);
		player->plane.y = oldPlaneX * sin(-5) + player->plane.y * cos(-5);
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
