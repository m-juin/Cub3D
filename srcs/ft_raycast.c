/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/05 15:26:58 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dvector ft_get_sided(t_dvector raydir, t_ivector map, t_dvector player,
							  t_dvector delta)
{
	t_dvector side;

	if (raydir.x < 0)
		side.x = (player.x - map.x) * delta.x;
	else
		side.x = (map.x + 1.0 - player.x) * delta.x;
	if (raydir.y < 0)
		side.y = (player.y - map.y) * delta.y;
	else
		side.y = (map.y + 1.0 - player.y) * delta.y;
	return (side);
}

static t_ivector ft_get_step(t_dvector raydir)
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

void ft_draw_ray3d(t_data *data)
{
	uint32_t x;
	double camera_x;
	t_dvector raydir;
	t_ivector map;
	t_dvector side_dist;
	t_dvector deltadist;
	double walldist;
	t_ivector step;
	int hit;
	int side;
	int lineh;
	int drawStart;
	int drawEnd;
	mlx_texture_t *used;

	x = 0;
	//ft_clean_img(data->img_3d);
	//ft_clean_img(data->img_ray);
	int w;
	w = 0;
	while (x < data->img_3d->width)
	{
		hit = 0;
		camera_x = 2 * x / (double)data->img_3d->width - 1;
		raydir.x = data->player->dir.x + data->player->plane.x * camera_x;
		raydir.y = data->player->dir.y + data->player->plane.y * camera_x;
		map.x = (int)data->player->map_pos.x;
		map.y = (int)data->player->map_pos.y;
		if (raydir.x == 0)
			deltadist.x = INFINITY;
		else
			deltadist.x = fabs(1 / raydir.x);
		if (raydir.y == 0)
			deltadist.y = INFINITY;
		else
			deltadist.y = fabs(1 / raydir.y);
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
		{
			walldist = (side_dist.x - deltadist.x);
			if (map.x < data->player->map_pos.x)
				used = data->east;
			else
				used = data->west;
		}
		else
		{
			walldist = (side_dist.y - deltadist.y);
			if (map.y < data->player->map_pos.y)
				used = data->south;
			else
				used = data->north;
		}
		lineh = (int)(data->img_3d->height / walldist);
		drawStart = -lineh / 2 + data->img_3d->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineh / 2 + data->img_3d->height / 2;
		if (drawEnd >= (int)data->img_3d->height)
			drawEnd = data->img_3d->height - 1;
		/*if (data->player->dir.y < 0 && data->player->dir.x < 0 )
			draw_line(data->img_ray, data->player->pos.x + data->player->img->width / 2, data->player->pos.y + data->player->img->height / 2, ((map.x - 1) * CSIZE), ((map.y - 1) * CSIZE), get_rgba(255, 0, 255, 60));
		else
			draw_line(data->img_ray, data->player->pos.x + data->player->img->width / 2, data->player->pos.y + data->player->img->height / 2, (map.x * CSIZE), (map.y * CSIZE), get_rgba(255, 0, 255, 60));*/
		double wallX;
		if (side == 0)
			wallX = data->player->map_pos.y + walldist * raydir.y;
		else
			wallX = data->player->map_pos.x + walldist * raydir.x;
		wallX -= floor((wallX));
		int texX = used->width - 1 - ((int)(wallX * (double)(used->width)));
		if (side == 0 && raydir.x > 0)
			texX = used->width - texX - 1;
		if (side == 1 && raydir.y < 0)
			texX = used->width - texX - 1;
		double step = 1.0 * used->height / lineh;
		// Starting texture coordinate
		double texPos = ((drawStart - data->img_3d->height / 2 + lineh / 2) * step);
		int y = 0;
		while (y < drawStart)
		{
			if (data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4)] != get_r(data->top) 
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 1] != get_g(data->top)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 2] != get_b(data->top)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 3] != get_a(data->top))
			{
				w++;
				mlx_put_pixel(data->img_3d, x, y, data->top);
			}
			y++;
		}
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = ((int)texPos & (used->height - 1));
			texPos += step;
			uint32_t color = get_rgba(used->pixels[used->width * (texY * 4) + (texX * 4)],
									  used->pixels[used->width * (texY * 4) + (texX * 4) + 1],
									  used->pixels[used->width * (texY * 4) + (texX * 4) + 2],
									  used->pixels[used->width * (texY * 4) + (texX * 4) + 3]);
			if (data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4)] != get_r(color) 
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 1] != get_g(color)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 2] != get_b(color)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 3] != get_a(color))
			{
				w++;
				mlx_put_pixel(data->img_3d, x, y, color);
			}
			y++;
		}
		while ((uint32_t)y < data->img_3d->height)
		{
			if (data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4)] != get_r(data->ground) 
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 1] != get_g(data->ground)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 2] != get_b(data->ground)
				|| data->img_3d->pixels[(y * 4) * data->img_3d->width + (x * 4) + 3] != get_a(data->ground))
			{
				w++;
				mlx_put_pixel(data->img_3d, x, y, data->ground);
			}
			y++;
		}
		// ft_print_lines_v3(data->img_3d, x, drawStart, drawEnd, 0);
		x++;
	}
	//printf ("Pixel draw = %i\n", w);
}
