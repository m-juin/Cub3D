/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/19 15:32:44 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_process_ray(t_data *data, t_calc_data *calc,
		t_draw_data *draw, t_ivector step)
{
	while (data->map[calc->map.y][calc->map.x] == '0'
		|| data->map[calc->map.y][calc->map.x] == '3')
	{
		if (calc->side_dist.x < calc->side_dist.y)
		{
			calc->side_dist.x += calc->delta_dist.x;
			calc->map.x += step.x;
			draw->side = 0;
		}
		else
		{
			calc->side_dist.y += calc->delta_dist.y;
			calc->map.y += step.y;
			draw->side = 1;
		}
	}
}

void	ft_draw_ray3d(t_data *data)
{
	double			camera_x;
	t_dvector		raydir;
	t_ivector		step;
	t_draw_data		draw_data;
	t_calc_data		calc_data;

	draw_data.width_pos = 0;
	while ((unsigned int)draw_data.width_pos < data->img_3d->width)
	{
		camera_x = 2 * draw_data.width_pos / (double)data->img_3d->width - 1;
		raydir.x = data->player->dir.x + data->player->plane.x * camera_x;
		raydir.y = data->player->dir.y + data->player->plane.y * camera_x;
		calc_data.map.x = (int)data->player->map_pos.x;
		calc_data.map.y = (int)data->player->map_pos.y;
		calc_data.delta_dist = ft_get_delta(raydir);
		calc_data.side_dist = ft_get_sided(raydir, calc_data.map,
				data->player->map_pos, calc_data.delta_dist);
		step = ft_get_step(raydir);
		ft_process_ray(data, &calc_data, &draw_data, step);
		ft_get_texture(data, &draw_data, &calc_data);
		draw_data.lineh = (int)(data->img_3d->height / calc_data.walldist);
		ft_draw_column(data, draw_data,
			ft_get_textx(data, raydir, draw_data, calc_data.walldist));
		draw_data.width_pos++;
	}
}
