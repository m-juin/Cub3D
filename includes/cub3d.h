/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:28:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 15:05:12 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h> 
# include <errno.h>

/* Window defines */

# define WIDTH 520
# define HEIGHT 520

typedef struct s_map_data{
	int	color;
	int	state;
}	t_map_data;

typedef struct s_player_data{
	int		py;
	int		px;
	float	pdx;
	float	pdy;
	float	pa;
	int		color;
	t_map_data **map_data;
}	t_player_data;

enum	e_dir
{
	north,
	south,
	east,
	west,
};

typedef struct s_data
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				ground;
	int				top;
	char			**map;
}	t_data;

typedef struct s_ivector
{
	int	x;
	int	y;
}	t_ivector;

typedef struct s_player
{
	t_ivector		map_pos;
	enum e_dir		facing_dir;
}	t_player;
typedef struct s_trash{
	t_map_data		**data;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player_data	*player;
}	t_trash;

typedef struct s_bresenham {
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		xincr;
	int		yincr;
	float	ey;
	float	ex;
	float	dy;
	float	dx;
	int		gdx;
	int		gdy;
}			t_bresenham;

/*	Utils/exit.c	*/
void	ft_exit(char *message, int exit_code);
void	ft_print_error(char *message);

/*	Utils/free.c	*/
void	*ft_double_free(char **array);
void	ft_free_data(t_data *data);

/*	Utils/colors.c	*/
int		get_rgba(int r, int g, int b, int a);
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

/*	Utils/empty_line.c	*/
int		ft_check_identifier_empty_line(char **id);
int		ft_line_is_empty(char *line);

/*	Parsing/ft_checkarg.c	*/
void	ft_checkarg(int ac, char **av);
int		ft_try_open(const char *path);

/*	Parsing/ft_checkmap.c	*/
void	ft_check_map(t_data *data);

/*	Parsing/ft_get_cub.c	*/
char	**ft_get_cub(const char *path);

/*	Parsing/ft_parse_data.c	*/
t_data	*ft_parse_data(char **identifiers, char **map);
char	*search_texture_path(char *identifier, char **data);

/*	Parsing/ft_get_rgb_from_id.c	*/
int		ft_get_rgb_from_id(char *id, char **data);

/*	Parsing/ft_parsing_main.c	*/
t_data	*ft_parsing_main(char *path);

/*	Parsing/ft_map_parsing.c	*/
char	**ft_parse_map(char **src);

/*	Mlx/key_hook.c	*/
void	handle_key_hook(mlx_key_data_t keydata, void *param);
/* ft_test.c */
void	ft_map_start(mlx_image_t *img, t_map_data ***data);
void	ft_put_player(mlx_image_t *img, t_trash *trash);
void	ft_print_lines(mlx_image_t *img, t_player_data *player);
void	ft_trace_ray(mlx_image_t *img, t_trash *trash);
void	ft_print_lines_v2(mlx_image_t *img, t_player_data *player, int rx, int ry);
void	ft_cast_rays(mlx_image_t *img, t_player_data *player);

#endif
