/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:48:54 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/25 12:38:20 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>
#define RAD M_PI/180.0

void	ft_dist_calc(t_player *player, t_raycast *raycast)
{
	raycast->dist = sqrt((player->px - raycast->dx) * (player->px - raycast->dx) + (raycast->dy - player->py) * (raycast->dy - player->py));
}

void	ft_cast_rays_vertical(t_player *player, t_raycast *raycast)
{
	//int	r;
	int	mx;
	int	my;
	//int	mp;
	int	dof;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	nTan;
	int		ratio;
	
	player->color = 0xFFFF0F0F;
	raycast->dx = player->px;
	raycast->dy = player->py;
	nTan = -tan(raycast->ra);
	dof = 0;
	ratio = 1;
	if (raycast->ra > M_PI_2 && raycast->ra < 3 * M_PI_2)
	{
		rx = (((int)player->px / ratio) * ratio) - 0.0001;
		ry = (player->px - rx) * nTan + player->py;
		xo = -ratio;
		yo = -xo * nTan;
	}
	else if (raycast->ra < M_PI_2 || raycast->ra > 3 * M_PI_2)
	{
		rx = (((int)player->px / ratio) * ratio) + ratio;
		ry = (player->px - rx) * nTan + player->py;
		xo = ratio;
		yo = -xo * nTan;
	}
	else if (raycast->ra == 0 || raycast->ra == M_PI)
	{
		rx = player->px;
		ry = player->py;
		dof = WIDTH;
	}
	while (dof < WIDTH)
	{
		mx = (int)rx / ratio;
		my = (int)ry / ratio;
		//mp = my * HEIGHT + mx;
		if (my < HEIGHT && mx < WIDTH && my >= 0 && mx >= 0 && player->map_data[my][mx].state == 1)
		{
			raycast->dx = rx;
			raycast->dy = ry;
			ft_dist_calc(player, raycast);
			dof = WIDTH;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
}

void	ft_cast_rays_horizontal(t_player *player, t_raycast *raycast)
{
	//int	r;
	int	mx;
	int	my;
	//int	mp;
	int	dof;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	aTan;
	int		ratio;
	
	raycast->dx = player->px;
	raycast->dy = player->py;
	player->color = 0xFFFF0F0F;
	aTan = -1 / tan(raycast->ra);
	dof = 0;
	ratio = 1;
	if (raycast->ra > M_PI)
	{
		ry = (((int)player->py / ratio) * ratio) - 0.0001;
		rx = (player->py - ry) * aTan + player->px;
		yo = -ratio;
		xo = -yo * aTan;
	}
	else if (raycast->ra < M_PI)
	{
		ry = (((int)player->py / ratio) * ratio) + ratio;
		rx = (player->py - ry) * aTan + player->px;
		yo = ratio;
		xo = -yo * aTan;
	}
	else if (raycast->ra == 0 || raycast->ra == M_PI)
	{
		rx = player->px;
		ry = player->py;
		dof = WIDTH;
	}
	while (dof < WIDTH)
	{
		mx = (int)rx / ratio;
		my = (int)ry / ratio;
		//mp = my * WIDTH + mx;
		if (my < HEIGHT && mx < WIDTH && my >= 0 && mx >= 0 && player->map_data[my][mx].state == 1)
		{
			raycast->dx = rx;
			raycast->dy = ry;
			ft_dist_calc(player, raycast);
			dof = WIDTH;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
}

void	ft_redraw_previous_ray(mlx_image_t *img, t_player *player)
{
	t_raycast	*horizontal;
	t_raycast	*vertical;

	horizontal = player->horizontal;
	vertical = player->vertical;
	if (vertical->dist == 1000000 && horizontal->dist == 1000000)
		return ;
	player->color = 0xFF0000FF;
	if (vertical->dist < horizontal->dist)
		ft_print_lines_v2(img, player, vertical->dx, vertical->dy);
	else if (horizontal->dist < vertical->dist)
		ft_print_lines_v2(img, player, horizontal->dx, horizontal->dy);
	player->color = 0x00F0FFFF;
}

void	ft_draw_3D(mlx_image_t *img, int i, float lineH, float lineOff)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		ft_print_lines_v3(img, i + j + 85, i + j + 85, lineOff, lineOff + lineH);
		j++;
	}
}

void	ft_fill_blank(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			mlx_put_pixel(img, y, x, 0);
			x++;
		}
		y++;
	}
}

void	ft_trace_correct_rays(mlx_image_t *img, t_player *player)
{
	t_raycast	*horizontal;
	t_raycast	*vertical;
	int			i;
	float		dist;
	float		lineH;
	float		lineO;

	i = 0;
	horizontal = player->horizontal;
	vertical = player->vertical;
	ft_fill_blank(img);
	//ft_redraw_previous_ray(img, player);
	horizontal->ra = player->pa - RAD * 30;
	if (horizontal->ra < 0)
		horizontal->ra += 2 * M_PI;
	if (horizontal->ra > 2 * M_PI)
		horizontal->ra -= 2 * M_PI;
	vertical->ra = horizontal->ra;
	while (i < 60)
	{
		ft_cast_rays_horizontal(player, horizontal);
		ft_cast_rays_vertical(player, vertical);
		if (vertical->dist < horizontal->dist)
		{
			//ft_print_lines_v2(img, player, vertical->dx, vertical->dy);
			dist = vertical->dist;
		}
		else if (horizontal->dist < vertical->dist)
		{
			//ft_print_lines_v2(img, player, horizontal->dx, horizontal->dy);
			dist = horizontal->dist;
		}
		horizontal->ra += RAD;
		if (horizontal->ra < 0)
			horizontal->ra += 2 * M_PI;
		if (horizontal->ra > 2 * M_PI)
			horizontal->ra -= 2 * M_PI;
		vertical->ra = horizontal->ra;
		lineH = (((WIDTH / 64) * (HEIGHT / 64)) * 320) / dist;
		if (lineH > 320)
			lineH = 320;
		lineO = 160 - ((int)lineH >> 1);
		ft_draw_3D(img, i * 8, lineH, lineO);
		i++;
	}
}

void	ft_trace_ray(mlx_image_t *img, t_data *trash)
{
	t_player *player;
	t_raycast	*horizontal;
	t_raycast	*vertical;

	player = malloc(sizeof(t_player) * 1);
	horizontal = malloc(sizeof(t_raycast) * 1);
	vertical = malloc(sizeof(t_raycast) * 1);
	trash->player = player;
	player->pa = M_PI * 1.25;
	player->color = 0x00F0FFFF;
	player->px = 85 + 4;
	player->py = 200 + 4;
	player->pdx = player->px + cos(player->pa) * 10;
	player->pdy = player->py + sin(player->pa) * 10;
	player->map_data = trash->pixel_map;
	vertical->dist = 1000000;
	horizontal->dist = 1000000;
	player->horizontal = horizontal;
	player->vertical = vertical;
	//ft_print_lines(img, player);
	ft_trace_correct_rays(img, player);
}

void	ft_map_start(mlx_image_t *img, t_pixel ***pixel_map)
{
	int	x;
	int	y;

	y = 0;
	*pixel_map = malloc(sizeof(t_pixel *) * HEIGHT);
	while (y < HEIGHT)
	{
		x = 0;
		(*pixel_map)[y] = malloc(sizeof(t_pixel) * WIDTH);
		while (x < WIDTH)
		{
			if (x < HEIGHT / 32 || y < WIDTH / 32 || x > WIDTH - WIDTH / 32 || y > HEIGHT - HEIGHT / 32)
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
	/*while (y < 8)
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
	}*/
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
