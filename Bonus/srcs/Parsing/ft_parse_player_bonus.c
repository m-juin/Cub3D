/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:11:32 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/15 15:43:48 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
				player->map_pos.x = pos.x;
				player->map_pos.y = pos.y;
				if (map[pos.y][pos.x] == 'N')
					player->facing_dir = north;
				else if (map[pos.y][pos.x] == 'S')
					player->facing_dir = south;
				else if (map[pos.y][pos.x] == 'E')
					player->facing_dir = east;
				else
					player->facing_dir = west;
				map[pos.y][pos.x] = '0';
			}
		}
	}
}

void	ft_get_rotation(enum e_dir start_dir, t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (start_dir == north)
	{
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->player_angle = 90;
	}
	else if (start_dir == south)
	{
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->player_angle = 270;
	}
	else if (start_dir == east)
	{
		player->dir.x = 1;
		player->plane.y = 0.66;
		player->player_angle = 0;
	}
	else
	{
		player->dir.x = -1;
		player->plane.y = -0.66;
		player->player_angle = 180;
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
	ft_get_rotation(player->facing_dir, player);
	player->map_pos.x += 0.5;
	player->map_pos.y += 0.5;
	player->pos.x = player->map_pos.x * CSIZE;
	player->pos.y = player->map_pos.y * CSIZE;
	player->minimap_pos.x = player->map_pos.x * MAP_CSIZE;
	player->minimap_pos.y = player->map_pos.y * MAP_CSIZE;
	player->minimap_pos.x = player->map_pos.x * MAP_CSIZE;
	player->minimap_pos.y = player->map_pos.y * MAP_CSIZE;
	if (player->minimap_pos.x > 128)
		player->player_center.x = 8 * MAP_CSIZE / 2 + MAP_CSIZE / 2;
	else
		player->player_center.x = 8 * MAP_CSIZE / 2 - MAP_CSIZE / 2;
	if (player->minimap_pos.y > 128)
		player->player_center.y = 8 * MAP_CSIZE / 2 + MAP_CSIZE / 2;
	else
		player->player_center.y = 8 * MAP_CSIZE / 2 - MAP_CSIZE / 2;
	player->minimap_offset.x = player->player_center.x - player->minimap_pos.x;
	player->minimap_offset.y = player->player_center.y - player->minimap_pos.y;
	player->target_pos = player->map_pos;
	player->target_dir = player->facing_dir;
	player->canmove = true;
	return (player);
}
