/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:40:59 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/18 17:42:40 by lobozier         ###   ########.fr       */
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

t_fvector	ft_horizontal_rays(t_data *data, float ray_angle)
{
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector	hor;
	t_ivector	map;
	float		dist_h;
	float		a_tan;
	int			offset;

	offset = 0;
	hor = data->player->minimap_pos;
	a_tan = -1 / tan(ray_angle);
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
		offset = data->msize.y;
	}
	while (offset < data->msize.y)
	{
		map.x = (int)ray_pos.x / MAP_CSIZE;
		map.y = (int)ray_pos.y / MAP_CSIZE;
		if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && (data->map[map.y][map.x] == '1' || data->map[map.y][map.x] == '2'))
		{
			hor = ray_pos;
			dist_h = dist(data->player->minimap_pos, ray_pos, ray_angle);
			offset = data->msize.y;
		}
		else
		{
			ray_pos.x += ray_offset.x;
			ray_pos.y += ray_offset.y;
			offset += 1;
		}
	}
	return (ray_pos);
}

t_fvector	ft_vertical_rays(t_data *data, float ray_angle)
{
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector	ver;
	t_ivector	map;
	float		dist_v;
	int			offset;
	float		v_tan;
	
	offset = 0;
	ver = data->player->minimap_pos;
	v_tan = tan(ray_angle);
	if (cos(ray_angle) > 0.001)
	{
		ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) + MAP_CSIZE;
		ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * v_tan + data->player->minimap_pos.y;
		ray_offset.x = MAP_CSIZE;
		ray_offset.y = -ray_offset.x * v_tan;
	}
	else if (cos(ray_angle) < -0.001)
	{
		ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) * MAP_CSIZE) - 0.0001;
		ray_pos.y = (data->player->minimap_pos.x - ray_pos.x) * v_tan + data->player->minimap_pos.y;
		ray_offset.x = -MAP_CSIZE;
		ray_offset.y = -ray_offset.x * v_tan;
	}
	else
	{
		ray_pos = data->player->minimap_pos;
		offset = data->msize.x;
	}
	while (offset < data->msize.x)
	{
		map.x = (int)ray_pos.x / MAP_CSIZE;
		map.y = (int)ray_pos.y / MAP_CSIZE;
		if (map.x > -1 && map.x < data->msize.x && map.y > -1 && map.y < data->msize.y && (data->map[map.y][map.x] == '1' || data->map[map.y][map.x] == '2'))
		{
			ver = ray_pos;
			dist_v = dist(data->player->minimap_pos, ray_pos, ray_angle);
			offset = data->msize.x;
		}
		else
		{
			ray_pos.x += ray_offset.x;
			ray_pos.y += ray_offset.y;
			offset += 1;
		}
	}
	return (ray_pos);
}

void	ft_draw_ray_minimap(t_data *data)
{
	int			r;
	float		ray_angle;
	t_fvector	ray_pos_ver;
	t_fvector	ray_pos_hor;
	float		dist_v;
	float		dist_h;

	r = 0;
	ft_clean_img(data->img_ray);
	ft_draw_minimap(data->img_map, data);
	ray_angle = deg_to_rad(fix_ang(data->player->player_angle - 32));
	while (r < 384)
	{
		ray_pos_ver = ft_vertical_rays(data, ray_angle);
		ray_pos_hor = ft_horizontal_rays(data, ray_angle);
		dist_v = dist(data->player->minimap_pos, ray_pos_ver, ray_angle);
		dist_h = dist(data->player->minimap_pos, ray_pos_hor, ray_angle);
		if (dist_h > 0 && dist_v > dist_h) 
			ray_pos_ver = ray_pos_hor;
		ray_pos_ver.x += data->player->minimap_offset.x;
		ray_pos_ver.y += data->player->minimap_offset.y;
		ft_print_lines(data->img_ray, data, ray_pos_ver);
		r++;
		ray_angle = ray_angle + DR / 6;
	}
}
