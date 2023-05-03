/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/03 15:47:55 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_fvector ft_get_sided(t_fvector raydir, t_ivector map, t_fvector player,
	t_fvector delta)
{
	t_fvector side;

	if (raydir.x < 0)
		side.x = (player.x - map.x) * delta.x;	
	else
		side.x = (map.x + 1 - player.x) * delta.x;	
	if (raydir.y < 0)
		side.y = (player.y - map.y) * delta.y;
	else
		side.y = (map.y + 1.0 - player.y) * delta.y;
	return (side);
}

static t_ivector ft_get_step(t_fvector raydir)
{
	t_ivector step;

	if (raydir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (raydir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

static void ft_dda(int lineh, t_data *data, int x)
{
	t_ivector linepos;

	linepos.x = (-lineh / 2 + data->img_3d->height / 2);
	if (linepos.x < 0)
		linepos.x = 0;
	linepos.y = (-lineh / 2 + data->img_3d->height / 2);
	if ((uint32_t)linepos.y >= data->img_3d->height)
		linepos.y = data->img_3d->height - 1;
	draw_line(data->img_3d, x, linepos.x, x, linepos.y, get_rgba(255, 255, 255, 255));
}

void	ft_draw_ray3d(t_data *data)
{
	uint32_t	x;
	float		camera_x;
	t_fvector	raydir;
	t_ivector	map;
	t_fvector	side_dist;
	t_fvector	deltadist;
	float		walldist;
	t_ivector	step;
	int			hit;
	int			side;
	int			lineh;

	x = 0;
	hit = 0;
	ft_clean_img(data->img_3d);
	while (x < data->img_3d->width)
	{
		camera_x = 2 * x / (float)data->img_3d->width - 1;
		raydir.x = data->player->dir.x + data->player->plane.x * camera_x;
		raydir.y = data->player->dir.y + data->player->plane.y * camera_x;
		map.x = (int)data->player->map_pos.x;
		map.y = (int)data->player->map_pos.y;
		if (raydir.x == 0)
			deltadist.x = INFINITY;
		else
			deltadist.x = fabsf(1 / raydir.x);
		if (raydir.y == 0)
			deltadist.y = INFINITY;
		else
			deltadist.y = fabsf(1 / raydir.y);
		side_dist = ft_get_sided(raydir, map, data->player->map_pos, deltadist);
		step = ft_get_step(raydir);
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += deltadist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += deltadist.y;
				map.y += step.y;
				side = 1;
			}
			if (data->map[map.y][map.x] == '1')
				hit = 1;
		}
		if (side == 0)
			walldist = (side_dist.x - deltadist.x);
		else
			walldist = (side_dist.y - deltadist.y);
		printf("begin = %u,	end = %f\n", data->img_3d->height, walldist);
		lineh = (int)(data->img_3d->height / walldist);
		ft_dda(lineh, data, x);
	}
}

