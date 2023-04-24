/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 08:30:27 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/22 14:26:23 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	ft_print_x_lines(mlx_image_t *img, t_bresenham *bre, int color)
{
	int	i;

	i = 0;
	while (i <= bre->dx)
	{
		if (bre->x1 > 0 && bre->x1 < 1000 && bre->y1 > 0 && bre->y1 < 1000)
			mlx_put_pixel(img, bre->x1, bre->y1, color);
		i++;
		bre->ex = bre->ex - bre->dy;
		if (bre->ex < 0)
		{
			bre->y1 = bre->y1 + bre->yincr;
			bre->ex = bre->ex + bre->dx;
		}
		bre->x1 = bre->x1 + bre->xincr;
	}
}

void	ft_print_y_lines(mlx_image_t *img, t_bresenham *bre, int color)
{
	int	i;

	i = 0;
	while (i <= bre->dy)
	{
		if (bre->x1 > 0 && bre->x1 < 1000 && bre->y1 > 0 && bre->y1 < 1000)
			mlx_put_pixel(img, bre->x1, bre->y1, color);
		i++;
		bre->ey = bre->ey - bre->dx;
		if (bre->ey < 0)
		{
			bre->x1 = bre->x1 + bre->xincr;
			bre->ey = bre->ey + bre->dy;
		}
		bre->y1 = bre->y1 + bre->yincr;
	}
}

void	ft_print_lines(mlx_image_t *img, t_player_data *player)
{
	t_bresenham *bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->y1 = player->py;
	bre->y2 = player->pdy;
	bre->x1 = player->px;
	bre->x2 = player->pdx;
	bre->ey = abs(bre->y2 - bre->y1);
	bre->ex = abs(bre->x2 - bre->x1);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->x1 > bre->x2)
		bre->xincr = -1;
	if (bre->y1 > bre->y2)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(img, bre, player->color);
	else
		ft_print_y_lines(img, bre, player->color);
	free(bre);
}

void	ft_print_lines_v2(mlx_image_t *img, t_player_data *player, int rx, int ry)
{
	t_bresenham *bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->y1 = player->py;
	bre->y2 = ry;
	bre->x1 = player->px;
	bre->x2 = rx;
	bre->ey = abs(bre->y2 - bre->y1);
	bre->ex = abs(bre->x2 - bre->x1);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->x1 > bre->x2)
		bre->xincr = -1;
	if (bre->y1 > bre->y2)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(img, bre, player->color);
	else
		ft_print_y_lines(img, bre, player->color);
	free(bre);
}
