/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_enemy_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:39:07 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/18 15:19:44 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <time.h>

static int	ft_count_empty(char **map, size_t map_width)
{
	t_ivector	pos;
	int			count;

	pos.y = 0;
	count = 0;
	while (map[pos.y] != NULL)
	{
		pos.x = 0;
		while (map[pos.y][pos.x] != '\0')
		{
			if (map[pos.y][pos.x] == '0')
				count++;
			pos.x++;
		}
		pos.y++;
	}
	if ((size_t)count <= map_width)
		return (0);
	return (count);
}

static t_enemy	**malloc_list(int count)
{
	t_enemy	**list;

	if (count == 0)
	{
		list = malloc(1 * sizeof(t_enemy *));
		if (list == NULL)
			return (NULL);
		list[0] = NULL;
		return (list);
	}
	count /= ENEMY_RATIO;
	list = malloc((count + 1) * sizeof(t_enemy *));
	if (list == NULL)
		return (NULL);
	list[count] = NULL;
	return (list);
}

static t_ivector	ft_get_random_pos(t_ivector mapsize)
{
	t_ivector	pos;

	pos.x = rand() % (mapsize.x - 1);
	pos.y = rand() % (mapsize.y - 1);
	return (pos);
}

static bool ft_is_valid(t_ivector npos, t_enemy **list, int pos, t_data *data)
{
	int pos2;

	pos2 = 0;
	if (npos.x == 0 || npos.y == 0 || npos.x == data->msize.x - 1
		|| npos.y == data->msize.y - 1)
		return (false);
	if (data->map[npos.y][npos.x] != '0')
		return (false);
	if (npos.x == data->player->map_pos.x || npos.y == data->player->map_pos.y)
		return (false);
	while (pos2 < pos)
	{
		if (list[pos2]->map_pos.x == npos.x || list[pos2]->map_pos.x == npos.y)
			return (false);
		pos2++;
	}
	return (true);
}

static bool ft_check_around(t_ivector *npos, t_enemy **list, int pos, t_data *data)
{
	if (ft_is_valid(*npos, list, pos, data) == true)
		return (true);
	npos->x += 1;
	if (ft_is_valid(*npos, list, pos, data) == true)
		return (true);
	npos->y += 1;
	if (ft_is_valid(*npos, list, pos, data) == true)
		return (true);
	npos->x -= 1;
	if (ft_is_valid(*npos, list, pos, data) == true)
		return (true);
	return (false);
}

static t_enemy	*ft_create_enemy(t_enemy **list, int pos, t_data *data)
{
	t_ivector	newpos;
	t_enemy		*new_enemy;

	newpos = ft_get_random_pos(data->msize);
	while (ft_check_around(&newpos, list, pos, data) == false)
		newpos = ft_get_random_pos(data->msize);
	new_enemy = malloc(1 * sizeof(t_enemy));
	if (new_enemy == NULL)
		return (NULL);
	new_enemy->map_pos.x = newpos.x;
	new_enemy->map_pos.y = newpos.y;
	return (new_enemy);
}

t_enemy	**ft_parse_enemy(t_data *data)
{
	int		count;
	int		pos;
	t_enemy	**list;

	count = ft_count_empty(data->map, data->msize.x);
	srand(time(NULL));
	list = malloc_list(count);
	if (list == NULL)
		return (NULL);
	count /= ENEMY_RATIO;
	pos = 0;
	while (pos < count)
	{
		//list[pos] = ft_create_enemy(list, pos, data);
		pos++;
	}
	return (list);
}
