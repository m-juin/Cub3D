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

static void	ft_exit(char *message, int exitcode)
{
	if (exitcode == 0)
		ft_printf_fd(1, "%s\n", message);
	else
		ft_printf_fd(2, "%s\n", message);
	exit(exitcode);
}

static void	ft_checkarg(int ac, char **av)
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

static void	ft_checkmap_empty(int fd)
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

static int	ft_mapcount_line(int fd)
{
	int		counter;
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

static void	ft_fill_map_array(int fd, char **map, int lcount)
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
	close(fd);
	map[pos] = NULL;
}

static void ft_double_free(char **array)
{
	unsigned int	pos;

	if (array == NULL)
		return ;
	pos = 0;
	while (array[pos] != NULL)
	{
		free(array[pos]);
		pos++;
	}
	free(array);
}

static void	free_map_data(t_map_data *data)
{
	if (data == NULL)
		return ;
	if (data->text_north != NULL)
		free(data->text_north);
	if (data->text_south != NULL)
		free(data->text_south);
	if (data->text_east != NULL)
		free(data->text_east);
	if (data->text_west != NULL)
		free(data->text_west);
	free(data);
}

static int	ft_map_open(char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error while opening file", 1);
	return (fd);
}

static int	ft_strfind(char *str, char *searched)
{
	unsigned int	pos;
	unsigned int	spos;

	pos = 0;
	while (str[pos] != '\0')
	{
		spos = 0;
		while (searched[spos] && searched[spos] == str[pos + spos])
			spos++;
		if (searched[spos] == '\0')
			return (pos);
		pos++;
	}
	return (-1);
}

static char *ft_mapget_text(char **map, char *flag)
{
	unsigned int	pos;
	int				nopos;
	char			*nostr;

	pos = 0;
	nopos = -1;
	while (map[pos] != NULL && nopos == -1)
	{
		nopos = ft_strfind(map[pos], flag);
		pos++;
	}
	if (nopos == -1)
		return (NULL);
	nopos += 2;
	while (map[pos - 1][nopos] == ' ')
		nopos++;
	nostr = ft_strdup(&map[pos - 1][nopos]);
	return (nostr);
}

static t_map_data *ft_mapget_textures(char **map)
{
	t_map_data	*map_data;

	map_data = malloc(1 * sizeof(t_map_data));
	if (map_data == NULL)
		return (NULL);
	map_data->text_north = ft_mapget_text(map, "NO ");
	map_data->text_south = ft_mapget_text(map, "SO ");
	map_data->text_east = ft_mapget_text(map, "EA ");
	map_data->text_west = ft_mapget_text(map, "WE ");
	if (map_data->text_north == NULL || map_data->text_south == NULL
		|| map_data->text_east == NULL || map_data->text_west == NULL)
	{
		free_map_data(map_data);
		return (NULL);
	}
	return (map_data);
}

static char	**ft_retrieve_map_data(int fd, char *map_path)
{
	int 	lcount;
	char	**map;

	lcount = ft_mapcount_line(fd);
	fd = ft_map_open(map_path);
	map = malloc((lcount + 1) * sizeof(char *));
	if (map == NULL)
	{
		close(fd);
		ft_exit("Error on first map array malloc", 1);
	}
	ft_fill_map_array(fd, map, lcount);
	return (map);
}

static t_map_data	*ft_mapget_content(char *map_path)
{
	int			fd;
	char		**unparsed_map;
	t_map_data	*map_data;

	fd = ft_map_open(map_path);
	ft_checkmap_empty(fd);
	unparsed_map = ft_retrieve_map_data(fd, map_path);
	map_data = ft_mapget_textures(unparsed_map);
	if (map_data == NULL)
	{
		ft_double_free(unparsed_map);
		ft_exit("Missing texture in map", 1);
	}
	ft_printf_fd(1, "North =%s\nSouth = %s\nEast = %s\nWest = %s\n", map_data->text_north, map_data->text_south, map_data->text_east, map_data->text_west);
	ft_exit("Valid map", 0);
	return (NULL);
}

static void	ft_checkmap_path(char *map_path)
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
		close(fd);
}

int	main(int ac, char **av)
{
	ft_checkarg(ac, av);
	ft_checkmap_path(av[1]);
	ft_mapget_content(av[1]);
 	/*mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Maze of DDD³", false);
	if (!mlx)
		ft_error();
	mlx_loop(mlx);
	mlx_terminate(mlx);*/
}
