/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:51 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/23 12:47:10 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_line_is_empty(char *line)
{
	size_t	pos;

	pos = 0;
	if (line[0] == '\n')
		return (1);
	while (line[pos] != '\0' && line[pos] == ' ')
		pos++;
	if (line[pos] != '\0')
	{
		return (-1);
	}
	return (1);
}

int	ft_check_identifier_empty_line(char **id)
{
	size_t	pos;
	size_t	lpos;

	pos = 0;
	while (id[pos] != NULL)
	{
		lpos = 0;
		while (id[pos][lpos] == ' ')
			lpos++;
		if (id[pos][lpos] != '\0' && id[pos][lpos] != '\n'
		&& ft_strncmp(&id[pos][lpos], "NO ", 3) != 0
		&& ft_strncmp(&id[pos][lpos], "SO ", 3) != 0
		&& ft_strncmp(&id[pos][lpos], "EA ", 3) != 0
		&& ft_strncmp(&id[pos][lpos], "WE ", 3) != 0
		&& ft_strncmp(&id[pos][lpos], "F ", 2) != 0
		&& ft_strncmp(&id[pos][lpos], "C ", 2) != 0)
		{
			ft_print_error("Invalid line in .cub");
			return (-1);
		}
		pos++;
	}
	return (1);
}
