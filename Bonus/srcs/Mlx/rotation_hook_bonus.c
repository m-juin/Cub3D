/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:00:28 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/23 11:45:00 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotation_hook(mlx_key_data_t keydata, t_player *pl)
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
