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

#include "cub3d.h"

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
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector	H;
	float		distH;
	float		distV;
	t_fvector	V;

	r = 0;
	ray_angle = fix_ang(90 + 30);
	H = data->player->minimap_pos;
	V = data->player->minimap_pos;
	while (r < 60)
	{
		distV = INFINITY;
		doffset = 0;
		nTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) - 0.0001;	
			ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * nTan + data->player->minimap_pos.y;
			ray_offset.x = -MAP_CSIZE;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else
		{
			ray_pos = data->player->minimap_pos;
			doffset = data->msize.y;
		}
		while (doffset < data->msize.y)
		{
			map.x = (int)(ray_pos.x) / MAP_CSIZE;
			map.y = (int)(ray_pos.y) / MAP_CSIZE;
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				//printf("oui\n");
				//printf("mapX = %d\tmapY = %d\n", map.x, map.y);
				V = ray_pos;
				distV = dist(data->player->minimap_pos, ray_pos, ray_angle);
				//printf("distV = %f\n", distV);
				doffset = data->msize.y;
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
			ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = -MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else if (sin(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
			ray_pos.x = (data->player->minimap_pos.y - ray_pos.y) * aTan + data->player->minimap_pos.x;
			ray_offset.y = MAP_CSIZE;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else 
		{
			ray_pos = data->player->minimap_pos;
			doffset = data->msize.x;
		}
		while (doffset < data->msize.x)
		{
			map.x = (int)(ray_pos.x) / MAP_CSIZE;
			map.y = (int)(ray_pos.y) / MAP_CSIZE;
			//printf("mapX = %d\tmapY = %d\n", map.x, map.y);	
			if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && data->map[map.y][map.x] == '1')
			{
				//printf("oui\n");
				//printf("mapX = %d\tmapY = %d\n", map.x, map.y);
				H = ray_pos;
				distH = dist(data->player->minimap_pos, ray_pos, ray_angle);
				//printf("distH = %f\n", distH);
				doffset = data->msize.x;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		ray_pos = H;
		if (distV < distH)
			ray_pos = V;
		//printf("minimap = %f\tmapX = %f\tmapY = %f\n", data->player->minimap_pos.x, ray_pos.x, ray_pos.y);
		//ft_print_lines_v3(data->img_ray, data->player->player_center.x, data->player->player_center.y, ray_pos.x, ray_pos.y);
		ft_print_lines_v3(data->img_ray, data->player->minimap_pos.x, data->player->minimap_pos.y, ray_pos.x, ray_pos.y);
		r++;
		ray_angle = fix_ang(ray_angle - 1);
	}
}
