/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fov_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:51:59 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/24 12:58:41 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_vertical_rays_bis(t_data *data, t_minimap *map)
{
	while (map->offset < data->msize.x)
	{
		map->map.x = (int)map->ray_pos.x / MAP_CSIZE;
		map->map.y = (int)map->ray_pos.y / MAP_CSIZE;
		if (map->map.x > -1 && map->map.x < data->msize.x && map->map.y > -1 && \
		map->map.y < data->msize.y && (data->map[map->map.y][map->map.x] != '0' \
		&& data->map[map->map.y][map->map.x] != '3'))
		{
			map->side = map->ray_pos;
			map->dist = dist(data->player->minimap_pos, \
			map->ray_pos, map->ray_angle);
			map->offset = data->msize.x;
		}
		else
		{
			map->ray_pos.x += map->ray_offset.x;
			map->ray_pos.y += map->ray_offset.y;
			map->offset += 1;
		}
	}
}

void	ft_vertical_rays(t_data *data, t_minimap *map)
{
	map->tan = tan(map->ray_angle);
	if (cos(map->ray_angle) > 0.001)
	{
		map->ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) \
		* MAP_CSIZE) + MAP_CSIZE;
		map->ray_pos.y = (data->player->minimap_pos.x - map->ray_pos.x) \
		* map->tan + data->player->minimap_pos.y;
		map->ray_offset.x = MAP_CSIZE;
		map->ray_offset.y = -map->ray_offset.x * map->tan;
	}
	else if (cos(map->ray_angle) < -0.001)
	{
		map->ray_pos.x = (((int)data->player->minimap_pos.x / MAP_CSIZE) \
		* MAP_CSIZE) - 0.0001;
		map->ray_pos.y = (data->player->minimap_pos.x - map->ray_pos.x) \
		* map->tan + data->player->minimap_pos.y;
		map->ray_offset.x = -MAP_CSIZE;
		map->ray_offset.y = -map->ray_offset.x * map->tan;
	}
	else
	{
		map->ray_pos = data->player->minimap_pos;
		map->offset = data->msize.x;
	}
	ft_vertical_rays_bis(data, map);
}

void	ft_horizontal_rays_bis(t_data *data, t_minimap *map)
{
	while (map->offset < data->msize.y)
	{
		map->map.x = (int)map->ray_pos.x / MAP_CSIZE;
		map->map.y = (int)map->ray_pos.y / MAP_CSIZE;
		if (map->map.x > -1 && map->map.x < data->msize.x && map->map.y > -1 && \
		map->map.y < data->msize.y && (data->map[map->map.y][map->map.x] != '0' \
		&& data->map[map->map.y][map->map.x] != '3'))
		{
			map->side = map->ray_pos;
			map->dist = dist(data->player->minimap_pos, map->ray_pos, \
			map->ray_angle);
			map->offset = data->msize.y;
		}
		else
		{
			map->ray_pos.x += map->ray_offset.x;
			map->ray_pos.y += map->ray_offset.y;
			map->offset += 1;
		}
	}
}

void	ft_horizontal_rays(t_data *data, t_minimap *map)
{
	map->tan = 1 / map->tan;
	if (sin(map->ray_angle) > 0.001)
	{
		map->ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) \
		* MAP_CSIZE) - 0.0001;
		map->ray_pos.x = (data->player->minimap_pos.y - map->ray_pos.y) \
		* map->tan + data->player->minimap_pos.x;
		map->ray_offset.y = -MAP_CSIZE;
		map->ray_offset.x = -map->ray_offset.y * map->tan;
	}
	else if (sin(map->ray_angle) < -0.001)
	{
		map->ray_pos.y = (((int)data->player->minimap_pos.y / MAP_CSIZE) \
		* MAP_CSIZE) + MAP_CSIZE;
		map->ray_pos.x = (data->player->minimap_pos.y - map->ray_pos.y) \
		* map->tan + data->player->minimap_pos.x;
		map->ray_offset.y = MAP_CSIZE;
		map->ray_offset.x = -map->ray_offset.y * map->tan;
	}
	else
	{
		map->ray_pos = data->player->minimap_pos;
		map->offset = data->msize.y;
	}
	ft_horizontal_rays_bis(data, map);
}
