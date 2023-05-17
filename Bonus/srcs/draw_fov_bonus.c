/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:30:35 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/17 15:17:34 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    ft_draw_fov(mlx_image_t *img, t_data *data, t_fvector ray_pos[])
{
    int r;
    t_fvector   ray_save;

    r = 0;
    while(r < 59)
    {
        ray_save = ray_pos[r];
        if (ray_save.x < ray_pos[r + 1].x)
        {
            while (ray_save.x < ray_pos[r + 1].x)
            {
                ray_save.x += 0.5;
                ft_print_lines(data->img_ray, data, ray_save);
            }
        }
        else if (ray_save.x > ray_pos[r + 1].x)
        {
            while (ray_save.x > ray_pos[r + 1].x)
            {
                ray_save.x -= 0.5;
                ft_print_lines(data->img_ray, data, ray_save);
            }
        }
        if (ray_save.y > ray_pos[r + 1].y)
        {
            while (ray_save.y > ray_pos[r + 1].y)
            {
                ray_save.y -= 0.5;
                ft_print_lines(data->img_ray, data, ray_save);
            }
        }
        else if (ray_save.y < ray_pos[r + 1].y)
        {
            while (ray_save.y < ray_pos[r + 1].y)
            {
                ray_save.y += 0.5;
                ft_print_lines(data->img_ray, data, ray_save);
            }
        }
        r++;
    }
}