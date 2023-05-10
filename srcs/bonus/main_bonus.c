/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:29:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/10 12:53:18 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*fill_image(int color, size_t x, size_t y, mlx_t *mlx)
{
	mlx_image_t	*img;
	size_t		posx;
	size_t		posy;

	img = mlx_new_image(mlx, x, y);
	if (img == NULL)
		return (NULL);
	posy = 0;
	while (posy < y)
	{
		posx = 0;
		while (posx < x)
		{
			mlx_put_pixel(img, posx, posy, color);
			posx++;
		}
		posy++;
	}
	return (img);
}

void	ft_clean_img(mlx_image_t *img_ray)
{
	t_ivector	pos;

	pos.y = 0;
	while (pos.y < (int)img_ray->height)
	{
		pos.x = 0;
		while (pos.x < (int)img_ray->width)
		{
			mlx_put_pixel(img_ray, pos.x, pos.y, get_rgba(0, 0, 0, 0));
			pos.x++;
		}
		pos.y++;
	}
}

static void	ft_update(void *param)
{
	t_data	*data;
	bool	mover;
	bool	rotr;

	data = (t_data *)param;
	mover = ft_move(data);
	rotr = ft_rotate(data);
	if (mover == true && rotr == true)
		data->player->canmove = true;
}

void	ft_free_data(t_data *data)
{
	mlx_delete_texture(data->east);
	mlx_delete_texture(data->west);
	mlx_delete_texture(data->north);
	mlx_delete_texture(data->south);
	free(data->player);
	ft_double_free(data->map);
	free(data);
}

int main(int ac, char **av)
{
	t_data	*data;

	ft_checkarg(ac, av);
	data = ft_parsing_main(av[1]);
	data->player = ft_parse_player(data->map);
	data->player->img = fill_image(get_rgba(75, 75, 75, 255), 8, 8, data->mlx);
	data->img_map = ft_draw_map(data);
	data->img_ray = fill_image(get_rgba(0, 0, 0, 0), data->msize.x * CSIZE, data->msize.y * CSIZE, data->mlx);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycast", true);
	data->img_3d = fill_image(get_rgba(0, 0, 0, 0), WIDTH, HEIGHT, data->mlx);
	mlx_image_to_window(data->mlx, data->img_3d, 0, 0);
	mlx_image_to_window(data->mlx, data->img_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->player->img, data->player->pos.x, data->player->pos.y);
	ft_draw_ray3d(data);
	mlx_key_hook(data->mlx, handle_key_hook, data);
	mlx_loop_hook(data->mlx, ft_update, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_free_data(data);
}