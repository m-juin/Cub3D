/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_column_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:46:49 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/09 13:48:57 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	toredraw(int x, int y, int color, t_data *data)
{
	size_t	pos;

	pos = (y * 4) * data->img_3d->width + (x * 4);
	if (data->img_3d->pixels[pos] != get_r(color)
		|| data->img_3d->pixels[pos + 1] != get_g(color)
		|| data->img_3d->pixels[pos + 2] != get_b(color)
		|| data->img_3d->pixels[pos + 3] != get_a(color))
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
