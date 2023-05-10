/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/10 11:02:44 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata, t_player *pl, t_data *data)
{
	t_dvector	target;

	target = collide(pl, data, keydata);
	if (target.x == pl->map_pos.x && target.y == pl->map_pos.y)
		return ;
	pl->target_pos = target;
	pl->canmove = false;
}

static void	rotation_hook(mlx_key_data_t keydata, t_player *pl)
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

static void	close_hook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key != MLX_KEY_ESCAPE || keydata.action != MLX_RELEASE)
		return ;
	mlx_terminate(data->mlx);
	ft_free_data(data);
	ft_exit("", 0);
}

void	handle_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->player->canmove == true)
	{
		movement_hook(keydata, data->player, data);
		rotation_hook(keydata, data->player);
	}
	close_hook(keydata, data);
}
