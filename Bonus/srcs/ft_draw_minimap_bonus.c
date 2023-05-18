/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:58:34 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/18 10:27:57 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_draw_case_map(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	if (toredraw(pos.x * MAP_CSIZE, pos.y * MAP_CSIZE, color, img) == false)
		return ;
	while (pos2.y < MAP_CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < MAP_CSIZE)
		{
			if ((pos.x * MAP_CSIZE) + pos2.x >= 0 && (pos.y * MAP_CSIZE) + pos2.y >= 0)
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

	pos.y = (int)data->player->minimap_pos.y / MAP_CSIZE - 4;
	minimap.y = 0;
	while (minimap.y < 8)
	{
		pos.x = (int)data->player->minimap_pos.x / MAP_CSIZE - 3;
		minimap.x = 0;
		while (minimap.x < 8)
		{
			if (pos.x >= data->msize.x || pos.y >= data->msize.y || pos.x < 0 || pos.y < 0)
				ft_draw_case_map(map, minimap, get_rgba(255, 255, 255, 25));
			else if (data->map[pos.y][pos.x] == '1')
				ft_draw_case_map(map, minimap, get_rgba(0, 0, 0, 255));
			else if (data->map[pos.y][pos.x] == '2')
				ft_draw_case_map(map, minimap, get_rgba(150, 0, 100, 255));
			else if (data->map[pos.y][pos.x] == '3')
				ft_draw_case_map(map, minimap, get_rgba(50, 100, 200, 255));
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