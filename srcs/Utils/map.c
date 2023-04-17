/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:21:59 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 11:22:22 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_map_array(int fd, char **map, int lcount)
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

int	ft_map_open(char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nError while opening file", 1);
	return (fd);
}
