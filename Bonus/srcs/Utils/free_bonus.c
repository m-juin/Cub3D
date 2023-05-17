/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:59:51 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/16 11:31:24 by mjuin            ###   ########.fr       */
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
	if (data->door != NULL)
		mlx_delete_texture(data->door);
	if (data->player != NULL)
		free(data->player);
	ft_double_free(data->map);
	free(data);
}
