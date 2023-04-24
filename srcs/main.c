/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 15:05:33 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

void	ft_move(void *data)
{
	t_trash *trash;

	trash = data;
	if (mlx_is_key_down(trash->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(trash->mlx);
	if (mlx_is_key_down(trash->mlx, MLX_KEY_DOWN))
	{
		trash->player->pa += 0.05;
		if (trash->player->pa > M_PI * 2)
			trash->player->pa -= (M_PI * 2);
		ft_cast_rays(trash->img, trash->player);
	}
	if (mlx_is_key_down(trash->mlx, MLX_KEY_UP))
	{
		trash->player->pa -= 0.05;
		if (trash->player->pa < 0)
			trash->player->pa += (M_PI * 2);
		ft_cast_rays(trash->img, trash->player);
	}
}

int	main(int ac, char **av)
{
	/*char	**array;
	t_data	*data;

	ft_checkarg(ac, av);
	array = ft_get_cub(av[1]);
	data = ft_parse_data(array);
	ft_double_free(array);
	if (data != NULL)
		free_data(data);*/
	t_trash	*trash;
 	
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ac = 0;
	av = NULL;
	trash = malloc(sizeof(t_trash) * 1);
	trash->mlx = mlx;
	trash->img = img;
	/*if (!mlx)
		ft_error();*/
	ft_map_start(img, &trash->data);
	ft_put_player(img, trash);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &ft_move, trash);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
