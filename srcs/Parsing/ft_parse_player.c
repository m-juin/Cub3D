/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:11:32 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/04 10:41:16 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_start(t_player *player, char **map)
{
	t_dvector	pos;

	pos.y = -1;
	while (map[(int)++pos.y] != NULL)
	{
		pos.x = -1;
		while (map[(int)pos.y][(int)++pos.x] != '\0')
		{
			if (map[(int)pos.y][(int)pos.x] == 'N' || map[(int)pos.y][(int)pos.x] == 'S'
				|| map[(int)pos.y][(int)pos.x] == 'E' || map[(int)pos.y][(int)pos.x] == 'W')
			{
				player->map_pos = pos;
				if (map[(int)pos.y][(int)pos.x] == 'N')
					player->facing_dir = north;
				else if (map[(int)pos.y][(int)pos.x] == 'S')
					player->facing_dir = south;
				else if (map[(int)pos.y][(int)pos.x] == 'E')
					player->facing_dir = east;
				else
					player->facing_dir = west;
				map[(int)pos.y][(int)pos.x] = '0';
				return ;
			}
		}
	}
}

static void	ft_get_rotation(enum e_dir start_dir, t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (start_dir == north)
	{
		player->dir.y = -1;
		player->plane.x = 0.66;
	}
	else if (start_dir == south)
	{
		player->dir.y = 1;
		player->plane.x = -0.66;
	}
	else if (start_dir == east)
	{
		player->dir.x = 1;
		player->plane.y = -0.66;
	}
	else
	{
		player->dir.x = -1;
		player->plane.y = 0.66;
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
	player->pos.x = player->map_pos.x * CSIZE + CSIZE / 2;
	player->pos.y = player->map_pos.y * CSIZE + CSIZE / 2;
	printf("PlayerX %f	PlayerY %f\n mapX %f	MapY %f\n", player->map_pos.x, player->map_pos.y, player->pos.x, player->pos.y);
	return (player);
}
