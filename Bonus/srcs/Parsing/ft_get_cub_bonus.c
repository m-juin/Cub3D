/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:04:23 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/21 11:21:46 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	**ft_fill_array(int fd, int lcount)
{
	char	*readed;
	int		pos;
	char	**map;

	pos = 0;
	map = malloc((lcount + 1) * sizeof(char *));
	if (map == NULL)
	{
		close(fd);
		ft_exit("Error\nMalloc fail to be done", 1);
	}
	while (pos < lcount)
	{
		readed = get_next_line(fd);
		map[pos] = readed;
		pos++;
	}
	get_next_line(fd);
	close(fd);
	map[pos] = NULL;
	return (map);
}

static int	ft_open(const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nError while opening file", 1);
	return (fd);
}

static int	ft_count_line(int fd)
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

char	**ft_get_cub(const char *path)
{
	int		fd;
	int		lcount;
	char	**map;

	fd = ft_open(path);
	lcount = ft_count_line(fd);
	fd = ft_open(path);
	map = ft_fill_array(fd, lcount);
	return (map);
}
