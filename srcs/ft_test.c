/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:48:54 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/24 16:41:54 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>

void	ft_cast_rays_horizontal(mlx_image_t *img, t_player *player)
{
	//int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	nTan;
	int		ratio;
	
	ra = player->pa;
	player->color = 0xFFFF0F0F;
	nTan = -1 / tan(ra);
	dof = 0;
	ratio = 1;
	if (ra > M_PI_2 && ra < 3 * M_PI_2)
	{
		ry = (((int)player->py / ratio) * ratio) - 0.0001;
		rx = (player->py - ry) * nTan + player->px;
		yo = -ratio;
		xo = -yo * nTan;
	}
	else if (ra < M_PI_2 || ra > 3 * M_PI_2)
	{
		ry = (((int)player->py / ratio) * ratio) + ratio;
		rx = (player->py - ry) * nTan + player->px;
		yo = ratio;
		xo = -yo * nTan;
	}
	else if (ra == 0 || ra == M_PI)
	{
		rx = player->px;
		ry = player->py;
		dof = WIDTH;
	}
	while (dof < WIDTH)
	{
		mx = (int)rx / ratio;
		my = (int)ry / ratio;
		mp = my * HEIGHT + mx;
		if (mp < WIDTH * HEIGHT && player->map_data[(int)ry][(int)rx].state == 1)
			dof = WIDTH;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	ft_print_lines_v2(img, player, rx, ry);
}

void	ft_cast_rays(mlx_image_t *img, t_player *player)
{
	//int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
	int		ratio;
	
	ra = player->pa;
	player->color = 0xFFFF0F0F;
	aTan = -1 / tan(ra);
	dof = 0;
	ratio = 1;
	if (ra > M_PI)
	{
		ry = (((int)player->py / ratio) * ratio) - 0.0001;
		rx = (player->py - ry) * aTan + player->px;
		yo = -ratio;
		xo = -yo * aTan;
	}
	else if (ra < M_PI)
	{
		ry = (((int)player->py / ratio) * ratio) + ratio;
		rx = (player->py - ry) * aTan + player->px;
		yo = ratio;
		xo = -yo * aTan;
	}
	else if (ra == 0 || ra == M_PI)
	{
		rx = player->px;
		ry = player->py;
		dof = WIDTH;
	}
	while (dof < WIDTH)
	{
		mx = (int)rx / ratio;
		my = (int)ry / ratio;
		mp = my * WIDTH + mx;
		if (mp < WIDTH * HEIGHT && player->map_data[my][mx].state == 1)
			dof = WIDTH;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	ft_print_lines_v2(img, player, rx, ry);
}

void	ft_trace_ray(mlx_image_t *img, t_data *trash)
{
	t_player *player;

	player = malloc(sizeof(t_player) * 1);
	trash->player = player;
	player->pa = M_PI * 1.25;
	player->color = 0x00F0FFFF;
	player->px = 85 + 4;
	player->py = 200 + 4;
	player->pdx = player->px + cos(player->pa) * 10;
	player->pdy = player->py + sin(player->pa) * 10;
	player->map_data = trash->pixel_map;
	ft_print_lines(img, player);
	ft_cast_rays(img, player);
}

void	ft_map_start(mlx_image_t *img, t_pixel ***pixel_map)
{
	int	x;
	int	y;

	y = 0;
	*pixel_map = malloc(sizeof(t_pixel *) * WIDTH);
	while (y < WIDTH)
	{
		x = 0;
		(*pixel_map)[y] = malloc(sizeof(t_pixel) * HEIGHT);
		while (x < HEIGHT)
		{
			if (x < HEIGHT/32 || y < WIDTH/32 || x > HEIGHT - HEIGHT/32 || y > WIDTH - WIDTH/32)
			{
				(*pixel_map)[y][x].color = 0x000000FF;
				(*pixel_map)[y][x].state = 1;
			}
			else
			{
				(*pixel_map)[y][x].color = 0xFF0000FF;
				(*pixel_map)[y][x].state = 0;
			}
			mlx_put_pixel(img, x, y, (*pixel_map)[y][x].color);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			(*pixel_map)[y+40][x+40].color = 0x000000FF;
			(*pixel_map)[y+40][x+40].state = 1;
			mlx_put_pixel(img, x+40, y+40, (*pixel_map)[y+40][x+40].color);
			(*pixel_map)[y+300][x+300].color = 0x000000FF;
			(*pixel_map)[y+300][x+300].state = 1;
			mlx_put_pixel(img, x+300, y+300, (*pixel_map)[y+300][x+300].color);
			x++;
		}
		y++;
	}
}

void	ft_put_player(mlx_image_t *img, t_data *trash)
{
	int	x;
	int	y;

	x = 0;
	while (x < 8)
	{
		y = 0;
		while (y < 8)
		{
			trash->pixel_map[y+200][x+85].color = 0x00F0FFFF;
			trash->pixel_map[y+200][x+85].state = 3;
			mlx_put_pixel(img, x+85, y+200, trash->pixel_map[y+200][x+85].color);
			y++;
		}
		x++;
	}
	ft_trace_ray(img, trash);
}
