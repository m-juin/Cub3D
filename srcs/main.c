/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/10 10:36:53 by mjuin            ###   ########.fr       */
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
		else
			return (good);
		if (data->player->target_dir == north && data->player->dir.y < -0.998 && data->player->dir.y > -1.002)
			good = true;
		else if (data->player->target_dir == south && data->player->dir.y < 1.002 && data->player->dir.y > 0.998)
			good = true;
		else if (data->player->target_dir == west && data->player->dir.x < -0.998 && data->player->dir.x > -1.002)
			good = true;
		else if (data->player->target_dir == east && data->player->dir.x < 1.002 && data->player->dir.x > 0.998)
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
	if (data->player->canmove == false && (((float)data->player->map_pos.x != (float)data->player->target_pos.x) || ((float)data->player->map_pos.y != (float)data->player->target_pos.y)))
	{
		if (data->player->map_pos.x < data->player->target_pos.x)
			data->player->map_pos.x += 0.05;
		else if (data->player->map_pos.x > data->player->target_pos.x)
			data->player->map_pos.x -= 0.05;
		if (data->player->map_pos.y > data->player->target_pos.y)
			data->player->map_pos.y -= 0.05;
		else if (data->player->map_pos.y < data->player->target_pos.y)
			data->player->map_pos.y += 0.05;	
		ft_draw_ray3d(data);
		if ((float)data->player->map_pos.x == (float)data->player->target_pos.x
			&& (float)data->player->map_pos.y == (float)data->player->target_pos.y)
		{
			return (true);
		}
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

void	ft_free_data(t_data *data)
{
	mlx_delete_texture(data->east);
	mlx_delete_texture(data->west);
	mlx_delete_texture(data->north);
	mlx_delete_texture(data->south);
	free(data->player);
	ft_double_free(data->map);
	free(data);
}

int main(int ac, char **av)
{
	t_data *data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	data->player = ft_parse_player(data->map);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycast", true);
	data->img_3d = fill_image(get_rgba(0, 0, 0, 0), WIDTH, HEIGHT, data->mlx);
	mlx_image_to_window(data->mlx, data->img_3d, 0, 0);
	ft_draw_ray3d(data);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_free_data(data);
}
