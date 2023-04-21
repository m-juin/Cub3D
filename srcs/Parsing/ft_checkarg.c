/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:06:12 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/21 11:21:57 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_try_open(const char *path)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error(strerror(errno));
		return (-1);
	}
	close(fd);
	return (1);
}

void	ft_checkarg(int ac, char **av)
{
	size_t	path_len;

	if (ac < 2 || ac > 2)
		ft_exit("Invalid argument amount (Need 1 argument)", 1);
	path_len = ft_strlen(av[1]);
	if (path_len <= 4)
		ft_exit("Invalid map path", 1);
	else if (ft_strfind(&av[1][path_len - 4], ".cub") == -1)
		ft_exit("Invalid map extension (.cub expected)", 1);
	if (ft_try_open(av[1]) == -1)
		exit(1);
}
