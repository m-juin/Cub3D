/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 08:30:27 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/11 12:16:11 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_x_lines(mlx_image_t *img, t_bresenham *bre)
{
	int	i;

	i = 0;
	while (i <= bre->dx)
	{
		if (bre->pos1.x > -1 && bre->pos1.x < WIDTH \
			&& bre->pos1.y > -1 && bre->pos1.y < HEIGHT)
		{
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, \
			get_rgba(0, 0, 0, 70));
		}
		i++;
		bre->ex = bre->ex - bre->dy;
		if (bre->ex < 0)
		{
			bre->pos1.y = bre->pos1.y + bre->yincr;
			bre->ex = bre->ex + bre->dx;
		}
		bre->pos1.x = bre->pos1.x + bre->xincr;
	}
}

void	ft_print_y_lines(mlx_image_t *img, t_bresenham *bre)
{
	int	i;

	i = 0;
	while (i <= bre->dy)
	{
		if (bre->pos1.x > -1 && bre->pos1.x < WIDTH && bre->pos1.y > -1
			&& bre->pos1.y < HEIGHT)
		{
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, \
			get_rgba(0, 0, 0, 70));
		}
		i++;
		bre->ey = bre->ey - bre->dx;
		if (bre->ey < 0)
		{
			bre->pos1.x = bre->pos1.x + bre->xincr;
			bre->ey = bre->ey + bre->dy;
		}
		bre->pos1.y = bre->pos1.y + bre->yincr;
	}
}

void	ft_print_lines_v3(mlx_image_t *img, int px, int py, int rx, int ry)
{
	t_bresenham	*bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->pos1.y = py;
	bre->pos2.y = ry;
	bre->pos1.x = px;
	bre->pos2.x = rx;
	bre->ey = abs(bre->pos2.y - bre->pos1.y);
	bre->ex = abs(bre->pos2.x - bre->pos1.x);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->pos1.x > bre->pos2.x)
		bre->xincr = -1;
	if (bre->pos1.y > bre->pos2.y)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(img, bre);
	else
		ft_print_y_lines(img, bre);
	free(bre);
}
