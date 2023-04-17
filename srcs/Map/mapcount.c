/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcount.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:18:03 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 11:18:16 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mapcount_line(int fd)
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
