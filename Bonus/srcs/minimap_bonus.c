/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:40:59 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/18 10:47:34 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	deg_to_rad(int angle)
{
	return (angle * DR);
}

float	dist(t_fvector a, t_fvector b, float angle)
{
	return (cos(deg_to_rad(angle)) * (b.x - a.x) - \
	sin(deg_to_rad(angle)) * (b.y - a.y));
}

int	fix_ang(int angle)
{
	if (angle > 358)
		angle -= 359;
	if (angle < -1)
		angle += 359;
	return (angle);
}

void	ft_draw_ray_minimap(t_data *data)
{
	int			r;
	int			doffset;
	t_ivector	map;
	float		ray_angle;
	float		a_tan;
	float		n_tan;
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector	hor;
	t_fvector	ver;
	float		dist_hor;
	float		dist_ver;

	r = 0;
	ft_clean_img(data->img_ray);
	ft_draw_minimap(data->img_map, data);
	ray_angle = deg_to_rad(fix_ang(data->player->player_angle - 32));
	hor = data->player->minimap_pos;
	ver = data->player->minimap_pos;
	while (r < 384)
	{
		dist_ver = INFINITY;
		doffset = 0;
		n_tan = tan(ray_angle);
		if (cos(ray_angle) > 0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * n_tan + data->player->minimap_pos.y;
			ray_offset.x = MAP_CSIZE;
			ray_offset.y = -ray_offset.x * n_tan;
		}
		else if (cos(ray_angle) < -0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * n_tan + data->player->minimap_pos.y;
			ray_offset.x = -MAP_CSIZE;
			ray_offset.y = -ray_offset.x * n_tan;
		}
		else
		{
			ray_pos = data->player->minimap_pos;
			doffset = data->msize.x;
		}
		while (doffset < data->msize.x)
		{
			map.x = (int)ray_pos.x / MAP_CSIZE;
			map.y = (int)ray_pos.y / MAP_CSIZE;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && (data->map[map.y][map.x] == '1' || data->map[map.y][map.x] == '2'))
			{
				ver = ray_pos;
				dist_ver = dist(data->player->minimap_pos, ray_pos, ray_angle);
				doffset = data->msize.x;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		dist_hor = INFINITY;
		doffset = 0;
		a_tan = 1.0f / n_tan;
		if (sin(ray_angle) > 0.001)
		{
			ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * a_tan + data->player->minimap_pos.x;
			ray_offset.y = -MAP_CSIZE;
			ray_offset.x = -ray_offset.y * a_tan;
		}
		else if (sin(ray_angle) < -0.001)
		{
			ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * a_tan + data->player->minimap_pos.x;
			ray_offset.y = MAP_CSIZE;
			ray_offset.x = -ray_offset.y * a_tan;
		}
		else
		{
			ray_pos = data->player->minimap_pos;
			doffset = data->msize.y;
		}
		while (doffset < data->msize.y)
		{
			map.x = (int)ray_pos.x / MAP_CSIZE;
			map.y = (int)ray_pos.y / MAP_CSIZE;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && (data->map[map.y][map.x] == '1' || data->map[map.y][map.x] == '2'))
			{
				hor = ray_pos;
				dist_hor = dist(data->player->minimap_pos, ray_pos, ray_angle);
				doffset = data->msize.y;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		ray_pos = hor;
		if (dist_ver < dist_hor)
			ray_pos = ver;
		ray_pos.x += data->player->minimap_offset.x;
		ray_pos.y += data->player->minimap_offset.y;
		ft_print_lines(data->img_ray, data, ray_pos);
		r++;
		ray_angle = ray_angle + DR / 6;
	}
}
