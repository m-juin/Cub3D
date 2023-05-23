/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:45:20 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/23 11:30:17 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ft_get_sep_line(char **id)
{
	size_t	pos;
	size_t	lpos;

	pos = 0;
	while (id[pos] != NULL)
	{
		lpos = 0;
		while (id[pos][lpos] != '\0' && id[pos][lpos] == ' ')
			lpos++;
		if (id[pos][lpos] == '1')
			return (pos);
		pos++;
	}
	return (-1);
}

char	**ft_get_map_part(char **src)
{
	int		sep;
	char	**mapped;
	size_t	pos;

	sep = ft_get_sep_line(src);
	if (sep == -1)
	{
		ft_print_error("No map part found in .cub");
		return (NULL);
	}
	pos = 0;
	while (src[sep + pos] != NULL)
		pos++;
	mapped = malloc((pos + 1) * sizeof(char *));
	if (mapped == NULL)
		return (NULL);
	pos = 0;
	while (src[sep + pos] != NULL)
	{
		mapped[pos] = ft_strdup(src[sep + pos]);
		pos++;
	}
	mapped[pos] = NULL;
	return (mapped);
}

static char	**ft_get_id_part(char **src)
{
	int		sep;
	char	**id;

	sep = ft_get_sep_line(src) + 1;
	if (sep == -1 || sep == 0)
	{
		ft_double_free(src);
		return (NULL);
	}
	id = malloc((sep) * sizeof(char *));
	if (id == NULL)
	{
		ft_double_free(src);
		return (NULL);
	}
	id[sep - 1] = NULL;
	sep--;
	while (sep > 0)
	{
		id[sep - 1] = ft_strdup(src[sep - 1]);
		sep--;
	}
	ft_double_free(src);
	return (id);
}

static t_ivector	ft_get_size(char **map)
{
	t_ivector	pos;
	t_ivector	size;

	pos.y = 0;
	size.x = 0;
	while (map[pos.y] != NULL)
	{
		pos.x = 0;
		while (map[pos.y][pos.x] != '\0')
			pos.x++;
		if (pos.x > size.x)
			size.x = pos.x;
		pos.y++;
	}
	size.y = pos.y;
	return (size);
}

void	ft_cursor_init(t_data *data)
{
	data->cursor = malloc(sizeof(t_cursor) * 1);
	if (data->cursor == NULL)
	{
		free(data);
		ft_exit("Error on malloc", 1);
	}
	data->cursor->prev_pos.x = -1;
	data->cursor->prev_pos.y = -1;
	data->cursor->side = south;
}

t_data	*ft_parsing_main(char *path)
{
	char		**identifiers;
	char		**mapped;
	t_data		*data;

	identifiers = ft_get_cub(path);
	mapped = ft_get_map_part(identifiers);
	identifiers = ft_get_id_part(identifiers);
	data = ft_parse_data(identifiers, mapped);
	ft_double_free(identifiers);
	ft_double_free(mapped);
	if (data == NULL)
		ft_exit("Error on malloc", 1);
	data->player = NULL;
	ft_cursor_init(data);
	ft_check_map(data);
	data->animation = ft_load_animation();
	if (data->animation == NULL)
	{
		ft_free_map_data(data);
		ft_exit("", 1);
	}
	data->msize = ft_get_size(data->map);
	return (data);
}
