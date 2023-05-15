/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:28:26 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/15 10:19:48 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_fill_array(char **filled, char **src, size_t size)
{
	size_t	lpos;

	lpos = 0;
	filled[size] = NULL;
	while (lpos < size)
	{
		filled[lpos] = ft_strtrim_end(src[lpos], " \n");
		lpos++;
	}
}

static char	**ft_get_proper_map(char **src)
{
	size_t	apos;
	char	**tmp;

	apos = 0;
	while (src[apos] != NULL && ft_line_is_empty(src[apos]) == -1)
		apos++;
	tmp = malloc((apos + 1) * sizeof(char *));
	if (tmp == NULL)
	{
		ft_print_error("Error on malloc");
		return (NULL);
	}
	ft_fill_array(tmp, src, apos);
	while (src[apos] != NULL && ft_line_is_empty(src[apos]) == 1)
		apos++;
	if (src[apos] != NULL)
	{
		ft_print_error("Invalid line in .cub");
		tmp = ft_double_free(tmp);
	}
	return (tmp);
}

static int	ft_is_valid_map_line(char *line)
{
	size_t			pos;
	static size_t	spawn = 0;

	if (line == NULL)
		return (-1);
	pos = 0;
	while (line[pos] != '\0')
	{
		if (line[pos] == 'N' || line[pos] == 'S' || line[pos] == 'W'
			|| line[pos] == 'E')
			spawn++;
		else if (line[pos] != '1' && line[pos] != '0' && line[pos] != ' '
			&& line[pos] != '2')
		{
			ft_print_error("Invalid character in map");
			return (-1);
		}
		pos++;
	}
	if (spawn > 1)
	{
		ft_print_error("Multiple player spawn point");
		return (-1);
	}
	return (1);
}

char	**ft_parse_map(char **src)
{
	size_t	apos;
	char	**map;

	map = ft_get_proper_map(src);
	if (map == NULL)
		return (NULL);
	apos = 0;
	while (map[apos] != NULL)
	{
		if (ft_is_valid_map_line(map[apos]) == -1)
		{
			ft_double_free(map);
			return (NULL);
		}
		apos++;
	}
	return (map);
}
