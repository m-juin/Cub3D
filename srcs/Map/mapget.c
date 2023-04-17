/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:13:17 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 11:30:05 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_mapget_text(char **map, char *flag)
{
	unsigned int	pos;
	int				nopos;
	char			*nostr;

	pos = 0;
	nopos = -1;
	while (map[pos] != NULL && nopos == -1)
	{
		nopos = ft_strfind(map[pos], flag);
		pos++;
	}
	if (nopos == -1)
		return (NULL);
	nopos += 2;
	while (map[pos - 1][nopos] == ' ')
		nopos++;
	nostr = ft_strdup(&map[pos - 1][nopos]);
	return (nostr);
}

static t_map_data	*ft_mapget_textures(char **map)
{
	t_map_data	*map_data;

	map_data = malloc(1 * sizeof(t_map_data));
	if (map_data == NULL)
		return (NULL);
	map_data->text_north = ft_mapget_text(map, "NO ");
	map_data->text_south = ft_mapget_text(map, "SO ");
	map_data->text_east = ft_mapget_text(map, "EA ");
	map_data->text_west = ft_mapget_text(map, "WE ");
	map_data->text_ground = ft_mapget_text(map, "F ");
	map_data->text_ceiling = ft_mapget_text(map, "C ");
	if (map_data->text_north == NULL || map_data->text_south == NULL
		|| map_data->text_east == NULL || map_data->text_west == NULL
		|| map_data->text_ground == NULL || map_data->text_ceiling == NULL)
	{
		free_map_data(map_data);
		return (NULL);
	}
	return (map_data);
}

static char	**ft_mapget_data(int fd, char *map_path)
{
	int		lcount;
	char	**map;

	lcount = ft_mapcount_line(fd);
	fd = ft_map_open(map_path);
	map = malloc((lcount + 1) * sizeof(char *));
	if (map == NULL)
	{
		close(fd);
		ft_exit("Error\nError on first map array malloc", 1);
	}
	ft_fill_map_array(fd, map, lcount);
	return (map);
}

t_map_data	*ft_mapget_content(char *map_path)
{
	int			fd;
	char		**unparsed_map;
	t_map_data	*map_data;

	fd = ft_map_open(map_path);
	ft_checkmap_empty(fd);
	unparsed_map = ft_mapget_data(fd, map_path);
	map_data = ft_mapget_textures(unparsed_map);
	if (map_data == NULL)
	{
		ft_double_free(unparsed_map);
		ft_exit("Error\nMissing texture in map", 1);
	}
	return (NULL);
}
