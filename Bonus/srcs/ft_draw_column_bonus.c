/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_column_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:05 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/18 10:26:50 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_draw_top(int end, t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < end)
	{
		if (toredraw(x, y, data->top, data->img_3d) == true)
			mlx_put_pixel(data->img_3d, x, y, data->top);
		y++;
	}
}

static void	ft_draw_floor(int start, t_data *data, int x)
{
	while ((unsigned int)start < data->img_3d->height)
	{
		if (toredraw(x, start, data->ground, data->img_3d) == true)
			mlx_put_pixel(data->img_3d, x, start, data->ground);
		start++;
	}
}

static void	ft_draw_wall(t_draw_data draw, t_data *data, int textx)
{
	double	texpos;
	double	step;
	int		color;
	int		texty;

	step = 1.0 * draw.text->height / draw.lineh;
	texpos = ((draw.pos.x - data->img_3d->height / 2 + draw.lineh / 2) * step);
	while (draw.pos.x < draw.pos.y)
	{
		texty = ((int)texpos & (draw.text->height - 1));
		texpos += step;
		color = get_color(textx, texty, draw.text);
		if (toredraw(draw.width_pos, draw.pos.x, color, data->img_3d) == true)
			mlx_put_pixel(data->img_3d, draw.width_pos, draw.pos.x, color);
		draw.pos.x++;
	}
}

void	ft_draw_column(t_data *data, t_draw_data draw, int textx)
{
	double		step;
	int			texpos;

	draw.pos = get_draw_data(draw.lineh, data->img_3d);
	step = 1.0 * draw.text->height / draw.lineh;
	texpos = ((draw.pos.x - data->img_3d->height / 2 + draw.lineh / 2) * step);
	ft_draw_top(draw.pos.x, data, draw.width_pos);
	ft_draw_wall(draw, data, textx);
	ft_draw_floor(draw.pos.y, data, draw.width_pos);
}
