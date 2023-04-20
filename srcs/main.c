/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/19 16:33:42 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	//ft_checkarg(ac, av);
	//ft_checkmap_path(av[1]);
	//ft_mapget_content(av[1]);
 	mlx_set_setting(MLX_STRETCH_IMAGE, true);
=======
/*   Updated: 2023/04/19 16:45:55 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	char	**array;
	t_data	*data;

	ft_checkarg(ac, av);
	array = ft_get_cub(av[1]);
	data = ft_parse_data(array);
	ft_double_free(array);
	if (data != NULL)
		free_data(data);
 	/*mlx_set_setting(MLX_STRETCH_IMAGE, true);
>>>>>>> master
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	/*if (!mlx)
		ft_error();*/
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
