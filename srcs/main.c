#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "MLX42.h"
#include "cub3D.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

/*static void ft_exit(char *message, int exitcode)
{
	if (exitcode == 0)
		ft_printf_fd(1,"%s\n", message);
	else
		ft_printf_fd(2, "%s\n", message);
	exit(exitcode);
}

static void ft_checkarg(int ac, char **av)
{
	if (ac != 2)
		ft_exit("invalid argument number", 1);
	if (ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".cub") != 0)
		ft_exit("invalid map extension", 1);
}*/

int main(int ac, char **av)
{
	(void)av;
	(void)ac;
	//ft_checkarg(ac, av);
	
 	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	if (!mlx)
		ft_error();
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
