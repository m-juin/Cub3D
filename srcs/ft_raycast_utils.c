/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:08:12 by lobozier          #+#    #+#             */
/*   Updated: 2023/04/28 09:10:46 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(int angle)
{
	return (angle * DR);
}

float	dist(t_fvector a, t_fvector b, float angle)
{
	return (cos(deg_to_rad(angle)) * (b.x - a.x) - \
			sin(deg_to_rad(angle)) * (b.y - a.y));
}

int	fix_ang(int angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}
