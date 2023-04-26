/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/26 17:37:45 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t *fill_image(int color, size_t x, size_t y, mlx_t *mlx)
{
	mlx_image_t	*img;
	size_t			posx;
	size_t			posy;

	img = mlx_new_image(mlx, x, y);
	if(img  == NULL)
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

void draw_line(mlx_image_t *img, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

static void	ft_clean_img(mlx_image_t *img_ray)
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

static void ft_draw_case(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	while (pos2.y < CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < CSIZE)
		{
			mlx_put_pixel(img, ((pos.x * CSIZE) + pos2.x) + pos.x + 1, ((pos.y * CSIZE) + pos2.y) + pos.y + 1, color);
			pos2.x++;
		}
		pos2.y++;
	}
}

static mlx_image_t *ft_draw_map(t_data *data)
{
	t_ivector			pos;
	mlx_image_t			*map;

	map = fill_image(get_rgba(255, 255, 255, 255), 8 * CSIZE + 9, 8 * CSIZE + 9, data->mlx);
	pos.y = 0;
	while (data->map[pos.y] != NULL)
	{
		pos.x = 0;
		while (data->map[pos.y][pos.x] != '\0')
		{
			if (data->map[pos.y][pos.x] == '1')
				ft_draw_case(map, pos, get_rgba(255, 0, 0, 255));
			else
				ft_draw_case(map, pos, get_rgba(1, 1, 1, 255));
			pos.x++;
		}
		pos.y++;
	}
	return (map);
}

static void	ft_draw_ray3d(t_player *player, mlx_image_t *map, mlx_image_t *ray_img)
{
	t_ivector	map_pos;
	//int			r;
	int			doffset;
	int			map_p;
	t_fvector	ray_pos;
	float		ray_angle;
	t_fvector	ray_offset;
	int			ray_count;
	float		atan;

	ray_angle = player->angle;
	ray_count = 0;
	while (ray_count < 1)
	{
		doffset = 0;
		ray_count++;
	}
	atan = -1 / tan(ray_angle);
	if (ray_angle > M_PI)
	{
		ray_pos.y = (((int)(player->pos.y + 4) >> 6) << 6) - 0.0001f;
		ray_pos.x = (player->pos.y + 4 - ray_pos.y) * atan + (player->pos.x + 4);
		ray_offset.y = (CSIZE * -1);
		ray_offset.x = (ray_offset.y * -1) * atan;
	}
	else if (ray_angle < M_PI)
	{
		ray_pos.y = (((int)(player->pos.y + 4) >> 6) << 6) + CSIZE;
		ray_pos.x = (player->pos.y + 4 - ray_pos.y) * atan + (player->pos.x + 4);
		ray_offset.y = CSIZE;
		ray_offset.x = ray_offset.y * atan;
	}
	else if (ray_angle == 0 || ray_angle == M_PI)
	{
		ray_pos.y = player->pos.y + 4;
		ray_pos.x = player->pos.x + 4;
		doffset = 8;
	}
	while (doffset < 8)
	{
		map_pos.x = (int)(ray_pos.x) >> 6;
		map_pos.y = (int)(ray_pos.y) >> 6;
		map_p = map_pos.y * 8 + map_pos.x;
		if (map_p < 8 * 8 && map->pixels[map_p] == (get_rgba(255, 0, 0, 255)))
		{
			doffset = 8;
		}
		else
		{
			ray_pos.x += ray_offset.x;
			ray_pos.y += ray_offset.y;
			doffset+=1;
		}
	}
	ft_clean_img(ray_img);
	draw_line(ray_img, (int)player->pos.x + 4, (int)player->pos.y + 4, (int)ray_pos.x, ray_pos.y, get_rgba(255, 255, 255, 255));
}

static void ft_update(void *param)
{
	//static int	frame;
	t_data		*data = (t_data *)param;

	/*if (frame != 60)
	{
		frame++;
		return ;
	}
	frame = 0;*/
	ft_draw_ray3d(data->player, data->img_map, data->img_ray);
	mlx_image_to_window(data->mlx, data->img_ray, 0, 0);
	return ;
}

int	main(int ac, char **av)
{
	t_data		*data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	data->player = ft_parse_player(data->map);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycast", true);
	data->player->img = fill_image(get_rgba(0, 255, 255, 255), 8, 8, data->mlx);
	data->img_map = ft_draw_map(data);
	data->img_ray = fill_image(get_rgba(0, 0, 0, 0), 8 * CSIZE + 9, 8 * CSIZE + 9, data->mlx);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->player->img, data->player->pos.x, data->player->pos.x);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
