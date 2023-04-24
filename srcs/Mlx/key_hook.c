/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:25 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 16:40:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_hook(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		printf("Going front\n");
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		printf("Going Back\n");
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		printf("Going Right\n");
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		printf("Going Left\n");
}

static void	rotation_hook(mlx_key_data_t keydata, t_data *trash)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		{
			trash->player->pa -= 0.05;
			if (trash->player->pa < 0)
				trash->player->pa += (M_PI * 2);
			ft_cast_rays(trash->img, trash->player);
		}
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		{
			trash->player->pa += 0.05;
			if (trash->player->pa > M_PI * 2)
				trash->player->pa -= (M_PI * 2);
			ft_cast_rays(trash->img, trash->player);
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
	movement_hook(keydata);
	rotation_hook(keydata, (t_data *)param);
	close_hook(keydata);
}
