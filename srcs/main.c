/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 10:50:49 by mjuin            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	*data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	/*if (!mlx)
		ft_error();*/
	mlx_image_t* img = mlx_texture_to_image(mlx, data->north);
	mlx_image_t* img2 = mlx_texture_to_image(mlx, data->south);
	mlx_image_t* img3 = mlx_texture_to_image(mlx, data->east);
	mlx_image_t* img4 = mlx_texture_to_image(mlx, data->west);
	mlx_image_t* img5 = fill_image(data->top, WIDTH, HEIGHT / 2, mlx);
	mlx_image_t* img6 = fill_image(data->ground, WIDTH, HEIGHT / 2, mlx);
	mlx_image_to_window(mlx, img5, 0, 0);
	mlx_image_to_window(mlx, img6, 0, HEIGHT / 2);
	mlx_image_to_window(mlx, img, (WIDTH / 2) - 128, 0);
	mlx_image_to_window(mlx, img2, (WIDTH / 2) - 128, (HEIGHT) - 256);
	mlx_image_to_window(mlx, img3, (WIDTH) - 256, (HEIGHT / 2) - 128);
	mlx_image_to_window(mlx, img4, 0, (HEIGHT / 2) - 128);
	mlx_key_hook(mlx, &handle_key_hook, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
