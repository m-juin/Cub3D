/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:58:34 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/15 15:23:40 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_case_map(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	while (pos2.y < MAP_CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < MAP_CSIZE)
		{
			mlx_put_pixel(img, ((pos.x * MAP_CSIZE) + pos2.x), ((pos.y * MAP_CSIZE) + pos2.y), color);
			pos2.x++;
		}
		pos2.y++;
	}
}

void	ft_draw_minimap(mlx_image_t *map, t_data *data)
{
	t_ivector			pos;
	t_ivector			minimap;

	pos.y = (int)data->player->map_pos.y - 4;
	minimap.y = 0;
	//printf("MapY = %f\t MapX= %f\n", data->player->map_pos.x, data->player->map_pos.y);
	while (minimap.y < 8)
	{
		pos.x = (int)data->player->map_pos.x - 3;
		minimap.x = 0;
		while (minimap.x < 8)
		{
			if (pos.x >= data->msize.x || pos.y >= data->msize.y || pos.x < 0 || pos.y < 0)
				ft_draw_case_map(map, minimap, get_rgba(255, 255, 255, 25));
			else if (data->map[pos.y][pos.x] == '1')
				ft_draw_case_map(map, minimap, get_rgba(0, 0, 0, 255));
			else if (data->map[pos.y][pos.x] == '2')
				ft_draw_case_map(map, minimap, get_rgba(150, 0, 100, 255));
			else if (data->map[pos.y][pos.x] == ' ')
				ft_draw_case_map(map, minimap, get_rgba(255, 255, 255, 25));
			else
				ft_draw_case_map(map, minimap, get_rgba(100, 100, 100, 255));	
			pos.x++;
			minimap.x++;
		}
		pos.y++;
		minimap.y++;
	}
}