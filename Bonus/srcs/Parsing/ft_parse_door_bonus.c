/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_door_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:39:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/19 10:57:11 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <time.h>

static t_door	**malloc_list(int count)
{
	t_door	**list;

	if (count == 0)
	{
		list = malloc(1 * sizeof(t_door *));
		if (list == NULL)
			return (NULL);
		list[0] = NULL;
		return (list);
	}
	list = malloc((count + 1) * sizeof(t_door *));
	if (list == NULL)
		return (NULL);
	list[count] = NULL;
	return (list);
}

static t_door	*ft_create_door(t_data *data, t_ivector pos)
{
	t_door		*door;
	size_t		count;

	door = malloc(1 * sizeof(t_door));
	if (door == NULL)
		return (NULL);
	door->map_pos.x = pos.x;
	door->map_pos.y = pos.y;
	count = 0;
	while (data->animation[count] != NULL)
		count++;
	door->anim_count = count - 1;
	door->animation = data->animation;
	if (door->anim_count != 0)
		door->anim_state = rand() % door->anim_count;
	else
		door->anim_state = 0;
	return (door);
}

static void	ft_fill_list(t_door **list, t_data *data)
{
	t_ivector	newpos;
	t_ivector	pos;
	int			count;

	pos.y = 0;
	count = 0;
	while (data->map[pos.y] != NULL)
	{
		pos.x = 0;
		while (data->map[pos.y][pos.x] != '\0')
		{
			if (data->map[pos.y][pos.x] == '2')
			{
				list[count] = ft_create_door(data, pos);
				count++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

t_door	**ft_parse_door(t_data *data)
{
	int		count;
	int		pos;
	t_door	**list;

	count = ft_count_door(data->map);
	list = malloc_list(count);
	if (list == NULL)
		return (NULL);
	srand(time(NULL));
	ft_fill_list(list, data);
	return (list);
}
