/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/18 10:37:02 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	movement_hook(mlx_key_data_t keydata, t_player *pl, t_data *data)
{
	t_dvector	target;

	target = collide(pl, data, keydata);
	if (target.x == pl->map_pos.x && target.y == pl->map_pos.y)
		return ;
	pl->target_pos = target;
	pl->canmove = false;
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *pl, t_data *data)
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

static t_ivector	get_looked(t_data *data)
{
	t_ivector	looked;

	looked.x = data->player->map_pos.x;
	looked.y = data->player->map_pos.y;
	if (data->player->facing_dir == north)
		looked.y -= 1;
	else if (data->player->facing_dir == south)
		looked.y += 1;
	else if (data->player->facing_dir == east)
		looked.x += 1;
	else
		looked.x -= 1;
	return (looked);
}

static void	door_hook(mlx_key_data_t keydata, t_data *data)
{
	t_ivector	looked;

	if (keydata.key != MLX_KEY_SPACE || keydata.action != MLX_RELEASE)
		return ;
	looked = get_looked(data);
	if (data->map[looked.y][looked.x] == '2')
	{
		data->map[looked.y][looked.x] = '3';
		ft_draw_ray3d(data);
		ft_draw_ray_minimap(data);
	}
	else if (data->map[looked.y][looked.x] == '3')
	{
		data->map[looked.y][looked.x] = '2';
		ft_draw_ray3d(data);
		ft_draw_ray_minimap(data);
	}
}

static void	close_hook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key != MLX_KEY_ESCAPE || keydata.action != MLX_RELEASE)
		return ;
	mlx_terminate(data->mlx);
	ft_free_map_data(data);
	ft_exit("", 0);
}

void	handle_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->player->canmove == true)
	{
		movement_hook(keydata, data->player, data);
		rotation_hook(keydata, data->player, data);
		door_hook(keydata, data);
	}
	close_hook(keydata, data);
}
