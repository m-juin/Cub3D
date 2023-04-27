/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/27 11:25:46 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player	*player, t_data *data)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->pos.x += player->delta.x;
		player->pos.y += player->delta.y;
		ft_draw_ray3d(data);
	}	
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->pos.x -= player->delta.x;
		player->pos.y -= player->delta.y;
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

int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

static void	rotation_hook(mlx_key_data_t keydata, t_player *player, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->angle -= 0.1f;
		if (player->angle < 0)
			player->angle += 2*PI;
		player->delta.x = cos(player->angle) * 5;
		player->delta.y = sin(player->angle) * 5;
		ft_draw_ray3d(data);
	}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		player->angle += 0.1f;
		if (player->angle > 2*PI)
			player->angle -= 2*PI;
		player->delta.x = cos(player->angle) * 5;
		player->delta.y = sin(player->angle) * 5;
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
