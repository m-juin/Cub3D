/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:40:59 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/20 13:10:47 by lobozier         ###   ########.fr       */
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

void	ft_init_map(t_minimap *map, t_data *data)
{
	map->offset = 0;
	map->dist = INFINITY;
	map->side = data->player->minimap_pos;
}

void	ft_draw_ray_minimap(t_data *data)
{
	int			r;
	t_fvector	ray_pos;
	t_minimap	map;
	float		dist_ver;

	r = 0;
	ft_clean_img(data->img_ray);
	ft_draw_minimap(data->img_map, data);
	map.ray_angle = deg_to_rad(fix_ang(data->player->player_angle - 32));
	while (r < 384)
	{
		ft_init_map(&map, data);
		ft_vertical_rays(data, &map);
		ray_pos = map.side;
		dist_ver = map.dist;
		ft_init_map(&map, data);
		ft_horizontal_rays(data, &map);
		if (dist_ver > map.dist)
			ray_pos = map.side;
		ray_pos.x += data->player->minimap_offset.x;
		ray_pos.y += data->player->minimap_offset.y;
		ft_print_lines(data->img_ray, data, ray_pos);
		r++;
		map.ray_angle = map.ray_angle + DR / 6;
	}
}
