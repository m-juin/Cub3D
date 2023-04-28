/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:11:32 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/28 12:19:43 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_start(t_player *player, char **map)
{
	t_ivector	pos;

	pos.y = -1;
	while (map[++pos.y] != NULL)
	{
		pos.x = -1;
		while (map[pos.y][++pos.x] != '\0')
		{
			if (map[pos.y][pos.x] == 'N' || map[pos.y][pos.x] == 'S'
				|| map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'W')
			{
				player->map_pos = pos;
				if (map[pos.y][pos.x] == 'N')
					player->facing_dir = north;
				else if (map[pos.y][pos.x] == 'S')
					player->facing_dir = south;
				else if (map[pos.y][pos.x] == 'E')
					player->facing_dir = east;
				else
					player->facing_dir = west;
				return ;
			}
		}
	}
}

t_player	*ft_parse_player(char **map)
{
	t_player	*player;

	if (map == NULL)
		return (NULL);
	player = malloc(1 * sizeof(t_player));
	if (player == NULL)
	{
		ft_print_error("Malloc error on player struct allocation");
		return (NULL);
	}
	ft_get_start(player, map);
	player->pos.x = player->map_pos.x * CSIZE + CSIZE / 2;
	player->pos.y = player->map_pos.y * CSIZE + CSIZE / 2;
	player->angle = 0.1f;
	player->delta.x = cos(player->angle) * 5;
	player->delta.y = sin(player->angle) * 5;
	
	return (player);
}
