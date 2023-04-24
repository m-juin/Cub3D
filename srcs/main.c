/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 16:40:13 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static mlx_image_t *fill_image(int color, size_t x, size_t y, mlx_t *mlx)
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
}*/


int	main(int ac, char **av)
{
	t_data	*trash;
 	
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ac = 0;
	av = NULL;
	trash = malloc(sizeof(t_data) * 1);
	trash->mlx = mlx;
	trash->img = img;
	ft_map_start(img, &trash->pixel_map);
	ft_put_player(img, trash);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_key_hook, trash);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
