/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:28:11 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/28 12:25:34 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_get_identifier_line(char *identifier, char **data)
{
	size_t	lcount;
	size_t	lpos;
	int		kpos;

	lcount = 0;
	kpos = -1;
	while (data[lcount] != NULL)
	{
		lpos = 0;
		while (data[lcount][lpos] == ' ')
			lpos++;
		if (ft_strncmp(&data[lcount][lpos], identifier,
			ft_strlen(identifier)) == 0 && kpos == -1)
			kpos = lcount;
		else if (ft_strncmp(&data[lcount][lpos], identifier,
			ft_strlen(identifier)) == 0 && kpos != -1)
		{
			ft_print_error("Double identifier");
			return (-1);
		}
		lcount++;
	}
	return (kpos);
}

char	*search_texture_path(char *identifier, char **data)
{
	size_t	lpos;
	int		kpos;
	char	*ret;

	kpos = ft_get_identifier_line(identifier, data);
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

static mlx_texture_t	*get_texture_from_id(char *id, char **data)
{
	char			*path;
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

t_data	*ft_parse_data(char **identifiers, char **map)
{
	t_data	*data;

	if (identifiers == NULL || map == NULL)
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
		ft_free_map_data(data);
		return (NULL);
	}
	return (data);
}
