/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/04 10:46:28 by lobozier         ###   ########.fr       */
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

void	ft_draw_ray3d(t_data *data)
{
	uint32_t	x;
	double		camera_x;
	t_dvector	raydir;
	t_ivector	map;
	t_dvector	side_dist;
	t_dvector	deltadist;
	double		walldist;
	t_ivector	step;
	int			hit;
	int			side;
	int			lineh;
	int			drawStart;
	int			drawEnd;

	x = 0;
	ft_clean_img(data->img_3d);
	ft_clean_img(data->img_ray);
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
		//printf("%d, %d\n", side_dist.x, side_dist.y);
		if (side == 0)
			walldist = (side_dist.x - deltadist.x);
		else
			walldist = (side_dist.y - deltadist.y);
		lineh = (int)(data->img_3d->height / walldist);
		drawStart = -lineh / 2 + data->img_3d->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineh / 2 + data->img_3d->height / 2;
		if (drawEnd >= (int)data->img_3d->height)
			drawEnd = data->img_3d->height - 1;
		draw_line(data->img_ray, data->player->pos.x, data->player->pos.y, map.x * 64, map.y * 64, get_rgba(255, 0, 255, 60));
		//ft_print_lines_v3(data->img_ray, x, drawStart, drawEnd, 0);
		//printf("%d --- %d\n", drawStart, drawEnd);
		//ft_dda(lineh, data, x);
		double wallX; // where exactly the wall was hit
		if (side == 0)
			wallX = data->player->map_pos.x + walldist * raydir.y;
		else
			wallX = data->player->map_pos.y + walldist * raydir.x;
		wallX -= floor((wallX));
      int texX = (int)(wallX * (double)(data->north->width));
	  if (side == 0 && raydir.x > 0)
			texX = data->north->width - texX - 1;
	  if (side == 1 && raydir.y < 0)
			texX = data->north->width - texX - 1;
	  double step = 1.0 * data->north->height / lineh;
	  // Starting texture coordinate
	  double texPos = (drawStart - data->img_3d->height / 2 + lineh / 2) * step;
	  for (int y = drawStart; y < drawEnd; y++)
	  {
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY =  (64 - (int)texPos & (data->north->height - 1));
			texPos += step;
			uint32_t color = get_rgba(data->north->pixels[data->north->width * (texY* 4) + (texX * 4)], 
			data->north->pixels[data->north->width * (texY* 4) + (texX * 4) + 1], 
			data->north->pixels[data->north->width * (texY* 4) + (texX * 4) + 2], 
			data->north->pixels[data->north->width * (texY* 4) + (texX * 4) + 3]);
			mlx_put_pixel(data->img_3d, x, y, color);
	  }
	  //ft_print_lines_v3(data->img_3d, x, drawStart, drawEnd, 0);
	  x++;
	}
}

