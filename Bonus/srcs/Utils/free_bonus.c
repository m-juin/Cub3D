/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:59:51 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/23 12:32:52 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*ft_double_free(char **array)
{
	unsigned int	pos;

	if (array == NULL)
		return (NULL);
	pos = 0;
	while (array[pos] != NULL)
	{
		free(array[pos]);
		pos++;
	}
	free(array);
	return (NULL);
}

static void	ft_simple_free(void *target)
{
	if (target != NULL)
		free(target);
}

static void	ft_free_door(t_door **door_list)
{
	int	pos;

	pos = 0;
	if (door_list == NULL)
		return ;
	while (door_list[pos] != NULL)
	{
		free(door_list[pos]);
		pos++;
	}
	free(door_list);
}

static void	ft_free_anim(mlx_texture_t **text)
{
	int	pos;

	pos = 0;
	if (text == NULL)
		return ;
	while (text[pos] != NULL)
	{
		mlx_delete_texture(text[pos]);
		pos++;
	}
	free(text);
}

void	ft_free_map_data(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->east != NULL)
		mlx_delete_texture(data->east);
	if (data->west != NULL)
		mlx_delete_texture(data->west);
	if (data->north != NULL)
		mlx_delete_texture(data->north);
	if (data->south != NULL)
		mlx_delete_texture(data->south);
	ft_free_door(data->door_list);
	ft_simple_free(data->player);
	ft_double_free(data->map);
	ft_free_anim(data->animation);
	free(data);
}
