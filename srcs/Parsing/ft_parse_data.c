/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:28:11 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/19 17:03:29 by mjuin            ###   ########.fr       */
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

t_data	*ft_parse_data(char **unparsed_data)
{
	t_data *data;

	if(unparsed_data == NULL)
		return (NULL);
	data = malloc(1 * sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->north = get_texture_from_id("NO ", unparsed_data);
	data->south = get_texture_from_id("SO ", unparsed_data);
	data->east = get_texture_from_id("EA ", unparsed_data);
	data->west = get_texture_from_id("WE ", unparsed_data);
	data->ground = ft_get_rgb_from_id("F ", unparsed_data);
	data->top = ft_get_rgb_from_id("C ", unparsed_data);
	if (data->north == NULL || data->south == NULL || data->east == NULL
		|| data->west == NULL || get_a(data->top < 255) || data->ground < 255)
		{
			free_data(data);
			return (NULL);
		}
	return (data);
}
