/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_rgb_from_id_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:07:01 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/23 14:55:11 by lobozier         ###   ########.fr       */
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
			return (-1);
		pos++;
	}
	if (pos > 3)
		return (-1);
	atoied = ft_atoi(str);
	if (atoied > 255 || atoied < 0)
		return (-1);
	return (1);
}

static char	**ft_ensured_split(char *str)
{
	char	**str_sp;

	str_sp = ft_split(str, ',');
	if (str_sp == NULL || str_sp[0] == NULL || str_sp[1] == NULL
		|| str_sp[2] == NULL || str_sp[3] != NULL)
	{
		ft_double_free(str_sp);
		return (NULL);
	}
	return (str_sp);
}

static int	color_from_str(char *str)
{
	char	**str_sp;
	int		pos;
	int		ret;

	pos = 0;
	str_sp = ft_ensured_split(str);
	if (str_sp == NULL)
		return (get_rgba(0, 0, 0, 1));
	while (pos < 3)
	{
		str_sp[pos] = ft_free_strtrim(str_sp[pos], " ");
		if (is_valid_rgb(str_sp[pos]) < 1)
		{
			ft_double_free(str_sp);
			return (get_rgba(0, 0, 0, 3));
		}
		pos++;
	}
	ret = get_rgba(ft_atoi(str_sp[0]), ft_atoi(str_sp[1]),
			ft_atoi(str_sp[2]), 255);
	ft_double_free(str_sp);
	return (ret);
}

static int	ft_count_occurence(char *src, char set)
{
	int	count;
	int	pos;

	count = 0;
	pos = 0;
	while (src[pos] != '\0')
	{
		if (src[pos] == set)
			count++;
		pos++;
	}
	return (count);
}

int	ft_get_rgb_from_id(char *id, char **data)
{
	char	*path;
	int		color;
	int		count;

	path = search_texture_path(id, data);
	if (path == NULL)
		return (get_rgba(0, 0, 0, 0));
	count = ft_count_occurence(path, ',');
	if (count != 2)
	{
		free(path);
		ft_print_error("Invalid RGB format");
		return (get_rgba(0, 0, 0, 0));
	}
	color = color_from_str(path);
	if (get_a(color) < 255)
		ft_print_error("Invalid RGB format");
	free(path);
	return (color);
}
