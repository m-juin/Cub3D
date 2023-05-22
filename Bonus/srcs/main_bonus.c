/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/22 10:54:22 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

mlx_image_t	*fill_image(int color, size_t x, size_t y, mlx_t *mlx)
{
	mlx_image_t	*img;
	size_t		posx;
	size_t		posy;

	img = mlx_new_image(mlx, x, y);
	if (img == NULL)
		return (NULL);
	posy = 0;
	while (posy < y)
	{
		posx = 0;
		while (posx < x)
		{
			mlx_put_pixel(img, posx, posy, color);
			posx++;
		}
		posy++;
	}
	return (img);
}

void	ft_clean_img(mlx_image_t *img_ray)
{
	t_ivector	pos;

	pos.y = 0;
	while (pos.y < (int)img_ray->height)
	{
		pos.x = 0;
		while (pos.x < (int)img_ray->width)
		{
			mlx_put_pixel(img_ray, pos.x, pos.y, get_rgba(0, 0, 0, 0));
			pos.x++;
		}
		pos.y++;
	}
}

static void ft_update_doors(t_door **door_list, t_data *data)
{
	int	pos;

	if (door_list[0]->anim_count == 0)
		return ;
	pos = 0;
	while (door_list[pos] != NULL)
	{
		door_list[pos]->speed_count++;
		if (door_list[pos]->speed_count >= door_list[pos]->anim_speed)
		{
			door_list[pos]->speed_count = 0;
			if (door_list[pos]->anim_state + 1 > door_list[pos]->anim_count)
				door_list[pos]->anim_state = 0;
			else
				door_list[pos]->anim_state++;
			ft_draw_ray3d(data);
		}
		pos++;
	}
}

static void	ft_update(void *param)
{
	t_data	*data;
	bool	mover;
	bool	rotr;

	data = (t_data *)param;
	mover = ft_move(data);
	rotr = ft_rotate(data);
	if (mover == true && rotr == true && data->player->canmove != true)
	{
		data->player->canmove = true;
		data->player->minimap_pos.x = data->player->map_pos.x * MAP_CSIZE;
		data->player->minimap_pos.y = data->player->map_pos.y * MAP_CSIZE;
		data->player->minimap_offset.x = data->player->player_center.x \
		- data->player->minimap_pos.x;
		data->player->minimap_offset.y = data->player->player_center.y \
		- data->player->minimap_pos.y;
		ft_draw_ray_minimap(data);
	}
	ft_update_doors(data->door_list, data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	data->player = ft_parse_player(data->map);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycast", true);
	data->player->img = fill_image(get_rgba(75, 200, 75, 255), 8, 8, data->mlx);
	data->img_map = fill_image(get_rgba(255, 255, 255, 255), \
	8 * MAP_CSIZE, 8 * MAP_CSIZE, data->mlx);
	data->img_ray = fill_image(get_rgba(0, 0, 0, 0), \
		8 * MAP_CSIZE, 8 * MAP_CSIZE, data->mlx);
	data->img_3d = fill_image(get_rgba(0, 0, 0, 0), WIDTH, HEIGHT, data->mlx);
	data->door_list = ft_parse_door(data);
	mlx_image_to_window(data->mlx, data->img_3d, 0, 0);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->player->img, \
	data->player->player_center.x - 4, data->player->player_center.y - 4);
	mlx_image_to_window(data->mlx, data->img_ray, 0, 0);
	ft_draw_ray_minimap(data);
	ft_draw_ray3d(data);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_free_map_data(data);
}
