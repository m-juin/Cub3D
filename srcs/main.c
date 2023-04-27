/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/27 11:38:04 by mjuin            ###   ########.fr       */
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
	double deltaX;
	double deltaY;
	int pixels;
	double pixelX;
	double pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY ;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		if (pixelX < 0 || pixelY < 0 || pixelX > img->width || pixelY > img->height)
			return ;
		--pixels;
	}
}

void	ft_draw_3D(mlx_image_t *img, float ax, float ay, float bx, float by, int color)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		ft_print_lines_v3(img, ax + j, ay, bx + j, by, color);
		j++;
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
			mlx_put_pixel(img, ((pos.x * CSIZE) + pos2.x), ((pos.y * CSIZE) + pos2.y), color);
			pos2.x++;
		}
		pos2.y++;
	}
}

float degToRad(int a) 
{
	return a*PI/180.0;
}


static float dist(t_fvector a, t_fvector b, float angle)
{
	return (sqrt((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}

static mlx_image_t *ft_draw_map(t_data *data)
{
	t_ivector			pos;
	mlx_image_t			*map;

	map = fill_image(get_rgba(255, 255, 255, 255), 8 * CSIZE, 8 * CSIZE, data->mlx);
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

void	ft_draw_ray3d(t_data *data)
{
	int	r = 0;
	int	doffset;
	t_ivector map;
	float	ray_angle;
	float	aTan;
	float	nTan;
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector H;
	float distH;
	float distV;
	float distT;
	t_fvector V;
	float LineH;
	float LineO;
	float Camera_angle;

	ft_clean_img(data->img_ray);
	ft_clean_img(data->img_3d);
	ray_angle = data->player->angle - DR*30;
	if (ray_angle < 0)
		ray_angle += 2*PI;
	if (ray_angle > 2*PI)
		ray_angle -= 2*PI;
	while (r < 60)
	{
		distH = 10000000;
		H.x = data->player->pos.x;
		H.y = data->player->pos.y;
		doffset = 0;
		aTan = -1 / tan(ray_angle);
		if (ray_angle > PI )
		{
			ray_pos.y = (((int)data->player->pos.y >> 6) << 6)-0.0001f;
			ray_pos.x = (data->player->pos.y - ray_pos.y) * aTan + data->player->pos.x;
			ray_offset.y = -64;
			ray_offset.x = -ray_offset.y * aTan;
		}
		if (ray_angle < PI)
		{
			ray_pos.y = (((int)data->player->pos.y >> 6) << 6) + 64;
			ray_pos.x = (data->player->pos.y - ray_pos.y) * aTan + data->player->pos.x;
			ray_offset.y = 64;
			ray_offset.x = -ray_offset.y * aTan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_pos.x = data->player->pos.x;
			ray_pos.y = data->player->pos.y;
			doffset = 8;
		}
		while (doffset < 8)
		{
			map.x = (int)(ray_pos.x) >> 6;
			map.y = (int)(ray_pos.y) >> 6;
			if (map.x > -1 && map.x < 8 && map.y > -1 && map.y < 8 && data->map[map.y][map.x] == '1')
			{
				H.x = ray_pos.x;
				H.y = ray_pos.y;
				distH = dist(data->player->pos, H , ray_angle);
				//printf("DistH = %f	X = %i	Y = %i\n", distH, map.x, map.y);
				doffset = 8;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		distV = 10000000;
		V.x = data->player->pos.x;
		V.y = data->player->pos.y;
		doffset = 0;
		nTan = -tan(ray_angle);
		if (ray_angle > P2 && ray_angle < P3)
		{
			ray_pos.x = (((int)data->player->pos.x >> 6) << 6)-0.0001f;
			ray_pos.y = (data->player->pos.x - ray_pos.x) * nTan + data->player->pos.y;
			ray_offset.x = -64;
			ray_offset.y = -ray_offset.x * nTan;
		}
		if (ray_angle < P2 || ray_angle > P3)
		{
			ray_pos.x = (((int)data->player->pos.x >> 6) << 6) + 64;
			ray_pos.y = (data->player->pos.x - ray_pos.x) * nTan + data->player->pos.y;
			ray_offset.x = 64;
			ray_offset.y = -ray_offset.x * nTan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_pos.x = data->player->pos.x;
			ray_pos.y = data->player->pos.y;
			doffset = 8;
		}
		while (doffset < 8)
		{
			map.x = (int)(ray_pos.x) >> 6;
			map.y = (int)(ray_pos.y) >> 6;
			if (map.x > -1 && map.x < 8 && map.y > -1 && map.y < 8 && data->map[map.y][map.x] == '1')
			{
				V.x = ray_pos.x;
				V.y = ray_pos.y;
				distV = dist(data->player->pos, V, ray_angle);
				//printf("DistV = %f	X = %i	Y = %i\n", distV, map.x, map.y);
				doffset = 8;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		if (distV < distH)
		{
			ray_pos.x = V.x;
			ray_pos.y = V.y;
			distT = distV;
		}
		else
		{
			ray_pos.x = H.x;
			ray_pos.y = H.y;
			distT = distH;
		}
		ft_print_lines_v3(data->img_ray, data->player->pos.x + 4, data->player->pos.y + 4, ray_pos.x, ray_pos.y, get_rgba(255, 255, 255, 255));
		Camera_angle = data->player->angle - ray_angle;
		if (Camera_angle < 0)
			Camera_angle += 2*PI;
		if (Camera_angle > 2*PI)
			Camera_angle -= 2*PI;
		distT = distT * cos(Camera_angle);
		LineH = (64 * HEIGHT) / distT;
		if(LineH > HEIGHT)
			LineH = HEIGHT;
		LineO = (HEIGHT / 2) - (LineH / 2);
		ft_draw_3D(data->img_3d, r * 8, LineO, r*8, LineH + LineO, get_rgba(255, 255, 0, 255));
		r++;
		ray_angle += DR;
		if (ray_angle < 0)
			ray_angle += 2*PI;
		if (ray_angle > 2*PI)
			ray_angle -= 2*PI;
	}
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
	data->img_ray = fill_image(get_rgba(0, 0, 0, 0), 8 * CSIZE, 8 * CSIZE, data->mlx);
	data->img_3d = fill_image(get_rgba(0, 0, 0, 0), 8 * CSIZE, 8 * CSIZE, data->mlx);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->img_3d, 521, 0);
	mlx_image_to_window(data->mlx, data->player->img, data->player->pos.x, data->player->pos.x);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
