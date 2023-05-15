/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:18:30 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/15 14:06:41 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_draw_case(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	while (pos2.y < CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < CSIZE)
		{
			mlx_put_pixel(img, ((pos.x * CSIZE) + pos2.x),
				((pos.y * CSIZE) + pos2.y), color);
			pos2.x++;
		}
		pos2.y++;
	}
}
