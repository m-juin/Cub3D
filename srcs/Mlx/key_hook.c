/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/05 13:09:33 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	t_dvector offset;

	offset.x = 0.5;
	offset.y = 0.5;
	if (player->dir.x < 0)
		offset.x = offset.x * -1;
	if (player->dir.y < 0)
		offset.y = offset.y * -1;
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		//printf("Map_posX = %d\tMap_posY = %d\tValue Map = %c\n", (int)player->map_pos.x, (int)player->map_pos.y, data->map[(int)(player->map_pos.x)][(int)player->map_pos.y]);
		if (data->map[(int)player->map_pos.y][(int)(player->map_pos.x + offset.x + player->dir.x * ROT)] != '1')
		{
			//player->pos.x += player->dir.x * ROT * CSIZE;
			player->map_pos.x += player->dir.x * ROT;
		}
		if (data->map[(int)(player->map_pos.y + offset.y + player->dir.y * ROT)][(int)(player->map_pos.x)] != '1')
		{
			//player->pos.y += player->dir.y * ROT * CSIZE;
			player->map_pos.y += player->dir.y * ROT;
		}
		//player->img->instances[0].x = player->pos.x;
		//player->img->instances[0].y = player->pos.y;
		ft_draw_ray3d(data);
	}	
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		//printf("Map_posX = %d\tMap_posY = %d\tPosX = %f\tPosY = %f\n", (int)player->map_pos.x, (int)player->map_pos.y, player->pos.x, player->pos.y);
		//printf("Map_posX = %d\tMap_posY = %d\tValue Map = %c\n", (int)player->map_pos.x, (int)player->map_pos.y, data->map[(int)(player->map_pos.x)][(int)player->map_pos.y]);
		if (data->map[(int)player->map_pos.y][(int)(player->map_pos.x + offset.x  - player->dir.x * ROT)] != '1')
		{
			//player->pos.x -= player->dir.x * ROT * CSIZE;
			player->map_pos.x -= player->dir.x * ROT;
		}
		if (data->map[(int)(player->map_pos.y + offset.y - player->dir.y * ROT)][(int)(player->map_pos.x)] != '1')
		{
			//player->pos.y -= player->dir.y * ROT * CSIZE;
			player->map_pos.y -= player->dir.y * ROT;
		}
		//player->img->instances[0].x = player->pos.x;
		//player->img->instances[0].y = player->pos.y;
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
		player->dir.x = player->dir.x * cos(-ROT) - player->dir.y * sin(-ROT);
		player->dir.y = oldDirX * sin(-ROT) + player->dir.y * cos(-ROT);
		player->plane.x = player->plane.x * cos(-ROT) - player->plane.y * sin(-ROT);
		player->plane.y = oldPlaneX * sin(-ROT) + player->plane.y * cos(-ROT);
		ft_draw_ray3d(data);
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->dir.x = player->dir.x * cos(ROT) - player->dir.y * sin(ROT);
		player->dir.y = oldDirX * sin(ROT) + player->dir.y * cos(ROT);
		player->plane.x = player->plane.x * cos(ROT) - player->plane.y * sin(ROT);
		player->plane.y = oldPlaneX * sin(ROT) + player->plane.y * cos(ROT);
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
	t_data *data;

	data = (t_data *)param;
	if (data->player->canmove == true)
	{
		movement_hook(keydata, data->player, data);
		rotation_hook(keydata, data->player, data);
	}
	close_hook(keydata);
}
