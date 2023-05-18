/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_animation_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:44:27 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/18 10:38:25 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*ft_get_path(int count)
{
	char	*iotaed;
	char	*path;

	iotaed = ft_itoa(count);
	path = ft_str_mega_join("./Assets/Textures/Animation/%s.png", iotaed);
	free(iotaed);
	return (path);
}

static int	ft_count_anim(void)
{
	int		fd;
	int		count;
	char	*path;

	fd = 0;
	count = 0;
	while (fd != -1)
	{
		path = ft_get_path(count);
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			count++;
		}
		if (path != NULL)
			free(path);
	}
	return (count);
}

static mlx_texture_t	*ft_load_texture(int count)
{
	mlx_texture_t	*text;
	char			*path;

	if (count < 0)
		return (NULL);
	path = ft_get_path(count);
	text = mlx_load_png(path);
	free(path);
	return (text);
}

mlx_texture_t	**ft_load_animation(void)
{
	int				size;
	mlx_texture_t	**list;

	size = ft_count_anim();
	if (size == 0)
	{
		ft_print_error("No enemy sprite");
		return (NULL);
	}
	list = malloc((size + 1) * sizeof(mlx_texture_t *));
	if (list == NULL)
		return (NULL);
	list[size] = NULL;
	size--;
	while (size >= 0)
	{
		list[size] = ft_load_texture(size);
		size--;
	}
	return (list);
}
