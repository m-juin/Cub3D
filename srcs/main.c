/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/05 15:30:37 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t *fill_image(int color, size_t x, size_t y, mlx_t *mlx)
{
	mlx_image_t *img;
	size_t posx;
	size_t posy;

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

void ft_clean_img(mlx_image_t *img_ray)
{
	t_ivector pos;

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

static bool ft_rotate(t_data *data)
{
	double oldDirX = data->player->dir.x;
	double oldPlaneX = data->player->plane.x;
	bool	good;

	good = false;
	if (data->player->canmove == false && data->player->target_dir != data->player->facing_dir)
	{
		if ((data->player->facing_dir == 0 && data->player->target_dir == 3)
			|| (data->player->facing_dir > data->player->target_dir && (data->player->target_dir != 0 || data->player->facing_dir != 3)))
		{
			data->player->dir.x = data->player->dir.x * cos(-ROT) - data->player->dir.y * sin(-ROT);
			data->player->dir.y = oldDirX * sin(-ROT) + data->player->dir.y * cos(-ROT);
			data->player->plane.x = data->player->plane.x * cos(-ROT) - data->player->plane.y * sin(-ROT);
			data->player->plane.y = oldPlaneX * sin(-ROT) + data->player->plane.y * cos(-ROT);
		}
		else if ((data->player->facing_dir == 3 && data->player->target_dir == 0)
			|| (data->player->facing_dir < data->player->target_dir))
		{
			data->player->dir.x = data->player->dir.x * cos(ROT) - data->player->dir.y * sin(ROT);
			data->player->dir.y = oldDirX * sin(ROT) + data->player->dir.y * cos(ROT);
			data->player->plane.x = data->player->plane.x * cos(ROT) - data->player->plane.y * sin(ROT);
			data->player->plane.y = oldPlaneX * sin(ROT) + data->player->plane.y * cos(ROT);
		}
		if (data->player->target_dir == north && data->player->dir.y < -0.999 && data->player->dir.y > -1.001)
			good = true;
		else if (data->player->target_dir == south && data->player->dir.y < 1.001 && data->player->dir.y > 0.999)
			good = true;
		else if (data->player->target_dir == west && data->player->dir.x < -0.999 && data->player->dir.x > -1.001)
			good = true;
		else if (data->player->target_dir == east && data->player->dir.x < 1.001 && data->player->dir.x > 0.999)
			good = true;
		if (good == true)
		{
			data->player->facing_dir = data->player->target_dir;
			ft_get_rotation(data->player->facing_dir, data->player);
			ft_draw_ray3d(data);
			return (true);
		}
		ft_draw_ray3d(data);
		return (false);
	}
	return (true);
}

static bool ft_move(t_data *data)
{
	if (data->player->canmove == false)
	{
		if (data->player->map_pos.x < data->player->target_pos.x)
			data->player->map_pos.x += 0.05;
		if (data->player->map_pos.x > data->player->target_pos.x)
			data->player->map_pos.x -= 0.05;
		if (data->player->map_pos.y > data->player->target_pos.y)
			data->player->map_pos.y -= 0.05;
		if (data->player->map_pos.y < data->player->target_pos.y)
			data->player->map_pos.y += 0.05;
		ft_draw_ray3d(data);
		if ((float)data->player->map_pos.x == (float)data->player->target_pos.x
			&& (float)data->player->map_pos.y == (float)data->player->target_pos.y)
			return (true);
		else
			return (false);
	}
	return (true);
}

static void ft_update(void *param)
{
	t_data	*data;
	bool	mover;
	bool	rotr;

	data = (t_data *)param;
	mover = ft_move(data);
	rotr = ft_rotate(data);
	if (mover == true && rotr == true)
		data->player->canmove = true;
}

int main(int ac, char **av)
{
	t_data *data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	data->player = ft_parse_player(data->map);
	// printf("PlayerX %f	PlayerY %f\n", player->map_pos.x, player->map_pos.y, player->pos.x, player->pos.y);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycast", true);
	// data->player->img = fill_image(get_rgba(0, 255, 255, 255), 8, 8, data->mlx);
	// data->img_map = ft_draw_map(data);
	// data->img_ray = fill_image(get_rgba(0, 0, 0, 0), data->msize.x * CSIZE, data->msize.y * CSIZE, data->mlx);
	data->img_3d = fill_image(get_rgba(0, 0, 0, 0), WIDTH, HEIGHT, data->mlx);
	// mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	// mlx_image_to_window(data->mlx, data->img_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->img_3d, 0, 0);
	// mlx_image_to_window(data->mlx, data->player->img, data->player->pos.x, data->player->pos.y);
	ft_draw_ray3d(data);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
