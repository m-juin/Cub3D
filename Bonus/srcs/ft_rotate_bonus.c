/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:44:10 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/23 12:57:04 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static bool	ft_rotate_bis(t_data *data, t_player *pl)
{
	bool	good;

	good = false;
	if (pl->target_dir == north && pl->dir.y < -0.998 && pl->dir.y > -1.002)
		good = true;
	else if (pl->target_dir == south && pl->dir.y < 1.002 && pl->dir.y > 0.998)
		good = true;
	else if (pl->target_dir == west && pl->dir.x < -0.998 && pl->dir.x > -1.002)
		good = true;
	else if (pl->target_dir == east && pl->dir.x < 1.002 && pl->dir.x > 0.998)
		good = true;
	if (good == true)
	{
		data->player->facing_dir = data->player->target_dir;
		ft_get_rotation(data->player->facing_dir, data->player);
		ft_draw_ray3d(data);
		ft_draw_ray_minimap(data);
		return (true);
	}
	ft_draw_ray3d(data);
	ft_draw_ray_minimap(data);
	return (false);
}

static void	ft_check_rot_2(t_data *data, double old_dir_x, double old_plane_x)
{
	data->player->dir.x = data->player->dir.x * cos(ROT) \
	- data->player->dir.y * sin(ROT);
	data->player->dir.y = old_dir_x * sin(ROT) \
	+ data->player->dir.y * cos(ROT);
	data->player->plane.x = data->player->plane.x * cos(ROT) \
	- data->player->plane.y * sin(ROT);
	data->player->plane.y = old_plane_x * sin(ROT) \
	+ data->player->plane.y * cos(ROT);
}

static bool	ft_check_rot_1(t_data *data, double old_dir_x, double old_plane_x)
{
	if ((data->player->facing_dir == north
			&& data->player->target_dir == west)
		|| (data->player->facing_dir > data->player->target_dir
			&& (data->player->target_dir != north
				|| data->player->facing_dir != west)))
	{
		data->player->dir.x = data->player->dir.x * cos(-ROT) \
		- data->player->dir.y * sin(-ROT);
		data->player->dir.y = old_dir_x * sin(-ROT) \
		+ data->player->dir.y * cos(-ROT);
		data->player->plane.x = data->player->plane.x * cos(-ROT) \
		- data->player->plane.y * sin(-ROT);
		data->player->plane.y = old_plane_x * sin(-ROT) \
		+ data->player->plane.y * cos(-ROT);
	}
	else if ((data->player->facing_dir == west
			&& data->player->target_dir == north)
		|| data->player->facing_dir < data->player->target_dir)
	{
		ft_check_rot_2(data, old_dir_x, old_plane_x);
	}
	else
		return (false);
	return (true);
}

bool	ft_rotate(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir.x;
	old_plane_x = data->player->plane.x;
	if (data->player->canmove == false && \
		data->player->target_dir != data->player->facing_dir)
	{
		if (ft_check_rot_1(data, old_dir_x, old_plane_x) == true \
		&& ft_rotate_bis(data, data->player) == true)
			return (true);
		return (false);
	}
	return (true);
}
