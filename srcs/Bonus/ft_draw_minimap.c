/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:58:34 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/10 12:41:18 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_case_map(mlx_image_t *img, t_ivector pos, int color)
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

mlx_image_t	*ft_draw_map(t_data *data)
{
	t_ivector			pos;
	mlx_image_t			*map;

	map = fill_image(get_rgba(255, 255, 255, 255), data->msize.x* MAP_CSIZE, data->msize.y * MAP_CSIZE, data->mlx);
	pos.y = 0;
	while (data->map[pos.y] != NULL)	
	{
		pos.x = 0;
		while (data->map[pos.y][pos.x] != '\0')
		{
			if (data->map[pos.y][pos.x] == '1')
				ft_draw_case_map(map, pos, get_rgba(255, 0, 0, 255));
			else if (data->map[pos.y][pos.x] == '2')
				ft_draw_case_map(map, pos, get_rgba(25, 50, 225, 255));
			else
				ft_draw_case_map(map, pos, get_rgba(1, 1, 1, 255));
			pos.x++;
		}
		pos.y++;
	}
	return (map);
}