/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/12 11:06:48by lobozier         ###   ########.fr       */
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
	float		aTan;
	float		nTan;
	t_fvector	ray_pos[60];
	t_fvector	ray_offset;
	t_fvector	H;
	t_fvector	V;
	float		distH;
	float		distV;

	r = 0;
	ft_clean_img(data->img_ray);
	ft_clean_img(data->img_map);
	ft_draw_minimap(data->img_map, data);
	ray_angle = fix_ang(data->player->player_angle + 30);
	H = data->player->minimap_pos;
	V = data->player->minimap_pos;
	while (r < 60)
	{
		distV = INFINITY;
		doffset = 0;
		nTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos[r].x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos[r].y = (data->player->minimap_pos.x - ray_pos[r].x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos[r].x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
			ray_pos[r].y = (data->player->minimap_pos.x - ray_pos[r].x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = -MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else
		{
			ray_pos[r] = data->player->minimap_pos;
			doffset = data->msize.x;
		}
		while (doffset < data->msize.x)
		{
			map.x = (int)ray_pos[r].x / MAP_CSIZE;
			map.y = (int)ray_pos[r].y / MAP_CSIZE;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				V = ray_pos[r];
				distV = dist(data->player->minimap_pos, ray_pos[r], ray_angle);
				doffset = data->msize.x;
			}
			else
			{
				ray_pos[r].x += ray_offset.x;
				ray_pos[r].y += ray_offset.y;
				doffset += 1;
			}
		}
		distH = INFINITY;
		doffset = 0;
		aTan = 1.0f / nTan;
		if (sin(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos[r].y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
			ray_pos[r].x = (data->player->minimap_pos.y - ray_pos[r].y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = -MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else if (sin(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos[r].y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos[r].x = (data->player->minimap_pos.y - ray_pos[r].y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else 
		{
			ray_pos[r] = data->player->minimap_pos;
			doffset = data->msize.y;
		}
		while (doffset < data->msize.y)
		{
			map.x = (int)ray_pos[r].x / MAP_CSIZE;
			map.y = (int)ray_pos[r].y / MAP_CSIZE;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				H = ray_pos[r];
				distH = dist(data->player->minimap_pos, ray_pos[r], ray_angle);
				doffset = data->msize.y;
			}
			else
			{
				ray_pos[r].x += ray_offset.x;
				ray_pos[r].y += ray_offset.y;
				doffset += 1;
			}
		}
		ray_pos[r] = H;
		if (distV < distH)
			ray_pos[r] = V;
		ray_pos[r].x += data->player->minimap_offset.x;
		ray_pos[r].y += data->player->minimap_offset.y;
		if (ray_pos[r].x < 0)
			ray_pos[r].x = 0;
		if (ray_pos[r].x > 256)
			ray_pos[r].x = 255;
		if (ray_pos[r].y < 0)
			ray_pos[r].y = 0;
		if (ray_pos[r].y > 256)
			ray_pos[r].y = 255;
		ft_print_lines_v3(data->img_ray, data, ray_pos[r]);
		r++;
		ray_angle = fix_ang(ray_angle - 1);
	}
}
