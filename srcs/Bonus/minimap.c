/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/11 12:07:58 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(int angle)
{
    return (angle * DR);
}

float	dist(t_dvector a, t_fvector b, float angle)
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
	int	r = 0;
	int	doffset;
	t_ivector map;
	float	ray_angle;
	float	aTan;
	float	nTan;
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector H;
	float distH;
	float distV;
	float distT;
	t_fvector V;

	//ft_clean_img(data->img_ray);
	//ft_clean_img(data->img_3d);
	ray_angle = fix_ang(90 + 30);
	H.x = data->player->minimap_pos.x;	
	H.y = data->player->minimap_pos.y;
	V = H;
	while (r < 60)
	{
		distV = INFINITY;
		doffset = 0;
		nTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x >> 5) << 5) + MAP_CSIZE;
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x >> 5) << 5) - 0.0001;	
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = -MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else
		{
			ray_pos.x = data->player->minimap_pos.x;
			ray_pos.y = data->player->minimap_pos.y;
			doffset = 8;
		}
		while (doffset < data->msize.x)
		{
			map.x = (int)(ray_pos.x) >> 5;
			map.y = (int)(ray_pos.y) >> 5;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				//printf("mapX = %d\tmapY = %d\tValmap = %c\n", map.x, map.y, data->map[map.y][map.x]);
				V.x = ray_pos.x;
				V.y = ray_pos.y;
				distV = dist(data->player->minimap_pos, ray_pos, ray_angle);
				doffset = data->msize.x;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		distH = INFINITY;
		doffset = 0;
		aTan = 1.0f / nTan;
		if (sin(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos.y = (((int)data->player->minimap_pos.y >> 5) << 5) - 0.0001;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = -MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else if (sin(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.y = (((int)data->player->minimap_pos.y >> 5) << 5) + MAP_CSIZE;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else 
		{
			ray_pos.x = data->player->minimap_pos.x;
			ray_pos.y = data->player->minimap_pos.y;
			doffset = 8;
		}
		while (doffset < data->msize.y)
		{
			map.x = (int)(ray_pos.x) >> 5;
			map.y = (int)(ray_pos.y) >> 5;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				//printf("mapX = %d\tmapY = %d\tValmap = %c\n", map.x, map.y, data->map[map.y][map.x]);
				H.x = ray_pos.x;
				H.y = ray_pos.y;
				distH = dist(data->player->minimap_pos, ray_pos, ray_angle);
				doffset = data->msize.y;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		if (distV < distH)
		{
			ray_pos.x = V.x;
			ray_pos.y = V.y;
			distT = distV;
		}
		else
		{
			ray_pos.x = H.x;
			ray_pos.y = H.y;
			distT = distH;
		}
		printf("mapX = %f\tmapY = %f\n", ray_pos.x, ray_pos.y);
		ft_print_lines_v3(data->img_ray, data->player->minimap_pos.x, data->player->minimap_pos.y, ray_pos.x, ray_pos.y);
		r++;
		ray_angle = fix_ang(ray_angle - 1);
	}
}
