/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:51:24 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 10:55:12 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_simple_free(void *arg)
{
	if (arg != NULL)
		free(arg);
	return (NULL);
}

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

void	free_map_data(t_map_data *data)
{
	if (data == NULL)
		return ;
	ft_simple_free(data->text_north);
	ft_simple_free(data->text_south);
	ft_simple_free(data->text_east);
	ft_simple_free(data->text_west);
	ft_simple_free(data->text_ground);
	ft_simple_free(data->text_ceiling);
	free(data);
}
