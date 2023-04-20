/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:28:11 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/20 14:40:18 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *search_texture_path(char *identifier, char **data)
{
	size_t	lcount;
	size_t	lpos;
	int		kpos;
	char	*ret;

	lcount = 0;
	kpos = -1;
	while (data[lcount] != NULL)
	{
		lpos = 0;
		while (data[lcount][lpos] == ' ')
			lpos++;
		if (ft_strncmp(&data[lcount][lpos], identifier, ft_strlen(identifier)) == 0 && kpos == -1)
			kpos = lcount;
		else if (ft_strncmp(&data[lcount][lpos], identifier, ft_strlen(identifier)) == 0 && kpos != -1)
		{
			ft_print_error("Double identifier");
			return (NULL);
		}
		lcount++;
	}
	if (kpos == -1)
	{
		ft_print_error("Missing identifier");
		return (NULL);
	}
	lpos = 0;
	while (data[kpos][lpos] == ' ')
		lpos++;
	lpos += 2;
	ret = ft_strtrim(&data[kpos][lpos], " \n");
	return (ret);
}

static mlx_texture_t *get_texture_from_id(char *id, char **data)
{
	char 			*path;
	size_t			path_len;
	mlx_texture_t	*text;

	path = search_texture_path(id, data);
	if (path == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	if (ft_strfind(&path[path_len - 4], ".png") == -1)
	{
		ft_print_error("Invalid texture(.png expected)");
		free(path);
		return (NULL);
	}
	if (ft_try_open(path) == -1)
	{
		free(path);
		return (NULL);
	}
	text = mlx_load_png(path);
	free(path);
	return (text);
}

static int	ft_line_is_empty(char *line)
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

static char **ft_get_proper_map(char **src)
{
	size_t	apos;
	size_t	lpos;
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
	tmp[apos] = NULL;
	lpos = 0;
	while (lpos < apos)
	{
		tmp[lpos] = ft_strtrim_end(src[lpos], " \n");
		lpos++;
	}
	while(src[apos] != NULL && ft_line_is_empty(src[apos]) == 1)
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
		else if (line[pos] != '1' && line[pos] != '0' && line[pos] != ' ')
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

static int	ft_check_identifier_empty_line(char **id)
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

static char	**ft_parse_map(char **src)
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

t_data	*ft_parse_data(char **identifiers, char **map)
{
	t_data *data;

	if(identifiers == NULL || map == NULL)
		return (NULL);
	if (ft_check_identifier_empty_line(identifiers) == -1)
		return (NULL);
	data = malloc(1 * sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->north = get_texture_from_id("NO ", identifiers);
	data->south = get_texture_from_id("SO ", identifiers);
	data->east = get_texture_from_id("EA ", identifiers);
	data->west = get_texture_from_id("WE ", identifiers);
	data->ground = ft_get_rgb_from_id("F ", identifiers);
	data->top = ft_get_rgb_from_id("C ", identifiers);
	data->map = ft_parse_map(map);
	if (data->north == NULL || data->south == NULL || data->east == NULL
		|| data->west == NULL || get_a(data->top) < 255 
		|| get_a(data->ground) < 255 || data->map == NULL)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
