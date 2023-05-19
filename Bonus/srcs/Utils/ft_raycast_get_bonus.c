/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_get_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:49:38 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/19 15:31:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_dvector	ft_get_sided(t_dvector raydir, t_ivector map, t_dvector pl,
							t_dvector delta)
{
	t_dvector	side;

	if (raydir.x < 0)
		side.x = (pl.x - map.x) * delta.x;
	else
		side.x = (map.x + 1.0 - pl.x) * delta.x;
	if (raydir.y < 0)
		side.y = (pl.y - map.y) * delta.y;
	else
		side.y = (map.y + 1.0 - pl.y) * delta.y;
	return (side);
}

t_ivector	ft_get_step(t_dvector raydir)
{
	t_ivector	step;

	if (raydir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (raydir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

int	ft_get_textx(t_data *data, t_dvector raydir,
		t_draw_data draw, double wall)
{
	int		textx;
	double	wallx;

	if (draw.side == 0)
		wallx = data->player->map_pos.y + wall * raydir.y;
	else
		wallx = data->player->map_pos.x + wall * raydir.x;
	wallx -= floor((wallx));
	textx = draw.text->width - 1 - ((int)(wallx * (double)(draw.text->width)));
	if (draw.side == 0 && raydir.x > 0)
		textx = draw.text->width - textx - 1;
	if (draw.side == 1 && raydir.y < 0)
		textx = draw.text->width - textx - 1;
	return (textx);
}

static	t_door *ft_get_door(t_ivector map_pos, t_door **doors)
{
	size_t pos;

	pos = 0;
	while (doors != NULL && doors[pos] != NULL)
	{
		if (doors[pos]->map_pos.x == map_pos.x
			&& doors[pos]->map_pos.y == map_pos.y)
		{
			return (doors[pos]);
		}
		pos++;
	}
	return (NULL);
}

void	ft_get_texture(t_data *data, t_draw_data *draw, t_calc_data *calc)
{
	t_door	*door;

	if (draw->side == 0)
	{
		calc->walldist = (calc->side_dist.x - calc->delta_dist.x);
		if (calc->map.x < data->player->map_pos.x)
			draw->text = data->east;
		else
			draw->text = data->west;
	}
	else
	{
		calc->walldist = (calc->side_dist.y - calc->delta_dist.y);
		if (calc->map.y < data->player->map_pos.y)
			draw->text = data->south;
		else
			draw->text = data->north;
	}
	if (data->map[calc->map.y][calc->map.x] == '2')
	{
		door = ft_get_door(calc->map, data->door_list);
		draw->text = door->animation[door->anim_state];
	}
}

t_dvector	ft_get_delta(t_dvector raydir)
{
	t_dvector	delta_dist;

	if (raydir.x == 0)
		delta_dist.x = INFINITY;
	else
		delta_dist.x = fabs(1 / raydir.x);
	if (raydir.y == 0)
		delta_dist.y = INFINITY;
	else
		delta_dist.y = fabs(1 / raydir.y);
	return (delta_dist);
}
