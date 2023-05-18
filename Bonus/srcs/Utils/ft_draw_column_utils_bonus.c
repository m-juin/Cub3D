/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_column_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:46:49 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/18 10:23:29 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	toredraw(int x, int y, int color, mlx_image_t *img)
{
	size_t	pos;

	pos = (y * 4) * img->width + (x * 4);
	if (img->pixels[pos] != get_r(color)
		|| img->pixels[pos + 1] != get_g(color)
		|| img->pixels[pos + 2] != get_b(color)
		|| img->pixels[pos + 3] != get_a(color))
		return (true);
	return (false);
}

int	get_color(int x, int y, mlx_texture_t *text)
{
	int		color;
	size_t	pos;

	pos = text->width * (y * 4) + (x * 4);
	color = get_rgba(text->pixels[pos], text->pixels[pos + 1],
			text->pixels[pos + 2],
			text->pixels[pos + 3]);
	return (color);
}

t_ivector	get_draw_data(int lineh, mlx_image_t *img)
{
	t_ivector	draw_data;

	draw_data.x = -lineh / 2 + img->height / 2;
	if (draw_data.x < 0)
		draw_data.x = 0;
	draw_data.y = lineh / 2 + img->height / 2;
	if (draw_data.y >= (int)img->height)
		draw_data.y = img->height - 1;
	return (draw_data);
}
