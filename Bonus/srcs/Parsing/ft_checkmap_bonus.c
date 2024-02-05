/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:44:17 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/16 10:42:17 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_ivector	ft_getstart(char **map)
{
	size_t		ypos;
	size_t		xpos;
	t_ivector	pos;

	ypos = 0;
	while (map[ypos] != NULL)
	{
		xpos = 0;
		while (map[ypos][xpos] != '\0')
		{
			if (map[ypos][xpos] == 'N' || map[ypos][xpos] == 'S'
				|| map[ypos][xpos] == 'E' || map[ypos][xpos] == 'W')
			{
				pos.x = xpos;
				pos.y = ypos;
				return (pos);
			}
			xpos++;
		}
		ypos++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

static void	ft_normalize_map(char **map)
{
	size_t	pos;
	size_t	len;
	size_t	strl;

	pos = 0;
	len = 0;
	while (map[pos] != NULL)
	{
		strl = ft_strlen(map[pos]);
		if (strl > len)
			len = strl;
		pos++;
	}
	pos = 0;
	while (map[pos] != NULL)
	{
		strl = ft_strlen(map[pos]);
		while (strl < len)
		{
			map[pos] = ft_addstr(map[pos], " ");
			strl++;
		}
		pos++;
	}
}

static int	ft_check_case(char **map, t_ivector pos)
{
	if (pos.x != 0 && map[pos.y][pos.x - 1] != '1'
		&& map[pos.y][pos.x - 1] != '0' && map[pos.y][pos.x - 1] != '2')
		return (-1);
	else if (pos.x == 0)
		return (-1);
	if (pos.y != 0 && map[pos.y - 1][pos.x] != '1'
		&& map[pos.y - 1][pos.x] != '0' && map[pos.y - 1][pos.x] != '2')
		return (-1);
	else if (pos.y == 0)
		return (-1);
	if (map[pos.y + 1] == NULL || (map[pos.y + 1][pos.x] != '1'
		&& map[pos.y + 1][pos.x] != '0' && map[pos.y + 1][pos.x] != '2'))
		return (-1);
	if (map[pos.y][pos.x + 1] != '1' && map[pos.y][pos.x + 1] != '0'
		&& map[pos.y][pos.x + 1] != '2')
		return (-1);
	return (1);
}

static int	ft_check_wall(char **map)
{
	t_ivector	pos;

	pos.y = 0;
	while (map[pos.y] != NULL)
	{
		pos.x = 0;
		while (map[pos.y][pos.x] != '\0')
		{
			if ((map[pos.y][pos.x] == '0' || map[pos.y][pos.x] == '2')
				&& ft_check_case(map, pos) == -1)
				return (-1);
			pos.x++;
		}
		pos.y++;
	}
	return (1);
}

void	ft_check_map(t_data *data)
{
	t_ivector	start;
	char		startvalue;

	start = ft_getstart(data->map);
	ft_normalize_map(data->map);
	if (start.x == -1)
	{
		ft_free_map_data(data);
		ft_exit("Can't reach player start pos", 1);
	}
	startvalue = data->map[start.y][start.x];
	data->map[start.y][start.x] = '0';
	if (ft_check_wall(data->map) == -1)
	{
		ft_free_map_data(data);
		ft_exit("Invalid map border", 1);
	}
	data->map[start.y][start.x] = startvalue;
}
