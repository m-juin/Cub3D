#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "MLX42.h"
#include "cub3D.h"

/*static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}*/

static void ft_exit(char *message, int exitcode)
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
}

/*static void *ft_simple_free(void *arg)
{
	if (arg != NULL)
		free(arg);
	return (NULL);
}*/

static void ft_checkmap_empty(int fd)
{
	ssize_t		readvalue;
	char		readed[2];

	readvalue = read(fd, readed, 1);
	if (readvalue == 0 || readvalue == -1)
	{
		close (fd);
		ft_exit("File is empty", 1);
	}
}

static int ft_mapcount_line(int fd)
{
	int 	counter;
	char	*readed;

	counter = 0;
	readed = get_next_line(fd);
	while (readed != NULL)
	{
		free(readed);
		readed = get_next_line(fd);
		counter++;
	}
	close (fd);
	return (counter);
}

static void ft_fill_map_array(int fd, char **map, int lcount)
{
	char			*readed;
	int				pos;

	pos = 0;
	while (pos < lcount)
	{
		readed = get_next_line(fd);
		map[pos] = ft_strtrim(readed, "\t\n ");
		free(readed);
		pos++;
	}
	map[pos] = NULL;
}

static int ft_map_open(char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error while opening file", 1);
	return (fd);
}

static char **ft_retrieve_map(int fd, char *map_path)
{
	int 	lcount;
	char	**map;

	lcount = ft_mapcount_line(fd);
	if (lcount < 9)
		ft_exit("Incomplete map", 1);
	fd = ft_map_open(map_path);
	map = malloc((lcount + 1) * sizeof(char *));
	if (map == NULL)
	{
		close(fd);
		ft_exit("Error on first map array malloc", 1);
	}
	ft_fill_map_array(fd, map, lcount);
	return (NULL);
}

static void ft_checkmap_content(char *map_path)
{
	int		fd;
	char	**unparsed_map;

	fd = ft_map_open(map_path);
	ft_checkmap_empty(fd);
	unparsed_map = ft_retrieve_map(fd, map_path);
}

static void ft_checkmap_path(char *map_path)
{
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
			ft_exit("Path is a directory", 1);
		else if (errno == EACCES)
			ft_exit("Invalid permission", 1);
		else if (errno == ENOENT)
			ft_exit("File doesn't exist", 1);
		else
			ft_exit("Error while opening file", 1);
	}
	else
	{
		close(fd);
	}
}

int main(int ac, char **av)
{
	ft_checkarg(ac, av);
	ft_checkmap_path(av[1]);
	ft_checkmap_content(av[1]);
 	/*mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	if (!mlx)
		ft_error();
	mlx_loop(mlx);
	mlx_terminate(mlx);*/
}
