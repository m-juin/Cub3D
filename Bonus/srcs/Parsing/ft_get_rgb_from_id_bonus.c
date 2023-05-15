/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_rgb_from_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:07:01 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/21 11:23:07 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_valid_rgb(char *str)
{
	size_t	pos;
	int		atoied;

	pos = 0;
	while (str[pos])
	{
		if (ft_isdigit(str[pos]) == 0)
			return (1);
		pos++;
	}
	atoied = ft_atoi(str);
	if (atoied > 255 || atoied < 0)
		return (-1);
	return (1);
}

static int	color_from_str(char *str)
{
	char	**splitted_str;
	int		pos;
	int		ret;

	pos = 0;
	splitted_str = ft_split(str, ',');
	if (splitted_str == NULL || splitted_str[0] == NULL
		|| splitted_str[1] == NULL || splitted_str[2] == NULL)
		return (get_rgba(0, 0, 0, 1));
	if (splitted_str[3] != NULL)
		return (get_rgba(0, 0, 0, 2));
	while (pos < 3)
	{
		splitted_str[pos] = ft_free_strtrim(splitted_str[pos], " ");
		if (is_valid_rgb(splitted_str[pos]) < 1)
		{
			ft_double_free(splitted_str);
			return (get_rgba(0, 0, 0, 3));
		}
		pos++;
	}
	ret = get_rgba(ft_atoi(splitted_str[0]), ft_atoi(splitted_str[1]),
			ft_atoi(splitted_str[2]), 255);
	ft_double_free(splitted_str);
	return (ret);
}

int	ft_get_rgb_from_id(char *id, char **data)
{
	char	*path;
	int		color;

	path = search_texture_path(id, data);
	if (path == NULL)
		return (get_rgba(0, 0, 0, 0));
	color = color_from_str(path);
	if (get_a(color) < 255)
		ft_print_error("Invalid RGB format");
	free(path);
	return (color);
}
