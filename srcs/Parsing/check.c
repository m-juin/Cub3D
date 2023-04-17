/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:58:48 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 11:02:09 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_checkmap_empty(int fd)
{
	ssize_t		readvalue;
	char		readed[2];

	readvalue = read(fd, readed, 1);
	if (readvalue == 0 || readvalue == -1)
	{
		close (fd);
		ft_exit("Error\nFile is empty", 1);
	}
}

void	ft_checkarg(int ac, char **av)
{
	if (ac != 2)
		ft_exit("Error\nInvalid argument number", 1);
	if (ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".cub") != 0)
		ft_exit("Error\nInvalid map extension", 1);
}

void	ft_checkmap_path(char *map_path)
{
	int			fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
			ft_exit("Error\nPath is a directory", 1);
		else if (errno == EACCES)
			ft_exit("Error\nInvalid permission", 1);
		else if (errno == ENOENT)
			ft_exit("Error\nFile doesn't exist", 1);
		else
			ft_exit("Error\nError while opening file", 1);
	}
	else
		close(fd);
}
