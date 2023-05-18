/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 08:30:27 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/18 11:36:15 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_print_x_lines(mlx_image_t *img, t_bresenham *bre, t_data *data)
{
	int	i;

	i = 0;
	while (i <= bre->delta.x)
	{
		if (data->map[(int)(bre->pos1.y - data->player->minimap_offset.y) / MAP_CSIZE][(int)(bre->pos1.x - data->player->minimap_offset.x) / MAP_CSIZE] == '1' || \
		data->map[(int)(bre->pos1.y - data->player->minimap_offset.y) / MAP_CSIZE][(int)(bre->pos1.x - data->player->minimap_offset.x) / MAP_CSIZE] == '2')
			return ;
		if (bre->pos1.x > -1 && bre->pos1.x < MAP_CSIZE * 8 \
			&& bre->pos1.y > -1 && bre->pos1.y < MAP_CSIZE * 8)
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, get_rgba(255, 255, 255, 70));
		i++;
		bre->error.x = bre->error.x - bre->delta.y;
		if (bre->error.x < 0)
		{
			bre->pos1.y = bre->pos1.y + bre->incr.y;
			bre->error.x = bre->error.x + bre->delta.x;
		}
		bre->pos1.x = bre->pos1.x + bre->incr.x;
	}
}

void	ft_print_y_lines(mlx_image_t *img, t_bresenham *bre, t_data *data)
{
	int	i;

	i = 0;
	while (i <= bre->delta.y)
	{
		if (data->map[(int)(bre->pos1.y - data->player->minimap_offset.y) / MAP_CSIZE][(int)(bre->pos1.x - data->player->minimap_offset.x) / MAP_CSIZE] == '1' || \
		data->map[(int)(bre->pos1.y - data->player->minimap_offset.y) / MAP_CSIZE][(int)(bre->pos1.x - data->player->minimap_offset.x) / MAP_CSIZE] == '2')
			return ;
		if (bre->pos1.x > -1 && bre->pos1.x < MAP_CSIZE * 8 && bre->pos1.y > -1
			&& bre->pos1.y < MAP_CSIZE * 8)
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, get_rgba(255, 255, 255, 70));
		i++;
		bre->error.y = bre->error.y - bre->delta.x;
		if (bre->error.y < 0)
		{
			bre->pos1.x = bre->pos1.x + bre->incr.x;
			bre->error.y = bre->error.y + bre->delta.y;
		}
		bre->pos1.y = bre->pos1.y + bre->incr.y;
	}	
}

void	ft_print_lines(mlx_image_t *img, t_data *data, t_fvector ray_pos)
{
	t_bresenham	*bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	if (!bre)
		return ;
	bre->pos1.y = data->player->player_center.y;
	bre->pos2.y = ray_pos.y;
	bre->pos1.x = data->player->player_center.x;
	bre->pos2.x = ray_pos.x;
	bre->error.y = abs(bre->pos2.y - bre->pos1.y);
	bre->error.x = abs(bre->pos2.x - bre->pos1.x);
	bre->delta = bre->error;
	bre->incr.x = 1;
	bre->incr.y = 1;
	if (bre->pos1.x > bre->pos2.x)
		bre->incr.x = -1;
	if (bre->pos1.y > bre->pos2.y)
		bre->incr.y = -1;
	if (bre->delta.x > bre->delta.y)
		ft_print_x_lines(img, bre, data);
	else
		ft_print_y_lines(img, bre, data);
	free(bre);
}
