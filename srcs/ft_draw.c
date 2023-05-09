/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:18:30 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/09 15:00:36 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY ;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		if (pixelX < 0 || pixelY < 0 || pixelX > img->width || pixelY > img->height)
			return ;
		--pixels;
	}
}

void	ft_draw_case(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	while (pos2.y < CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < CSIZE)
		{
			mlx_put_pixel(img, ((pos.x * CSIZE) + pos2.x), ((pos.y * CSIZE) + pos2.y), color);
			pos2.x++;
		}
		pos2.y++;
	}
}