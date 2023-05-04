/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:28:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/04 10:27:15 by lobozier         ###   ########.fr       */
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
# include <math.h>

/* Window defines */

# define WIDTH	1016
# define HEIGHT	512
# define CSIZE	64
# define P3 3* M_PI_2
# define DR M_PI / 180
# define ROT 1.5f
enum	e_dir
{
	north,
	south,
	east,
	west,
};

typedef struct s_ivector
{
	int	x;
	int	y;
}	t_ivector;

typedef struct s_dvector
{
	double	x;
	double	y;
}	t_dvector;

typedef struct s_fvector
{
	float	x;
	float	y;
}	t_fvector;

typedef struct s_pixel
{
	int	color;
	int	state;
}	t_pixel;

typedef struct s_player
{
	t_dvector	map_pos;
	enum e_dir	facing_dir;
	t_fvector	pos;
	t_dvector	dir;
	t_dvector	plane;
	mlx_image_t	*img;
}	t_player;

typedef struct s_data
{
	/*t_pixel			**pixel_map;*/
	mlx_t			*mlx;
	mlx_image_t		*img_ray;
	mlx_image_t		*img_3d;
	mlx_image_t		*img_map;
	t_player		*player;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int				ground;
	int				top;
	char			**map;
	t_ivector		msize;
}	t_data;

typedef struct s_bresenham 
{
	t_ivector pos1;
	t_ivector pos2;
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
void		ft_exit(char *message, int exit_code);
void		ft_print_error(char *message);

/*	Utils/free.c	*/
void		*ft_double_free(char **array);
void		ft_free_map_data(t_data *data);

/*	Utils/colors.c	*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

/*	Utils/empty_line.c	*/
int			ft_check_identifier_empty_line(char **id);
int			ft_line_is_empty(char *line);

/*	Parsing/ft_checkarg.c	*/
void		ft_checkarg(int ac, char **av);
int			ft_try_open(const char *path);

/*	Parsing/ft_checkmap.c	*/
void		ft_check_map(t_data *data);

/*	Parsing/ft_get_cub.c	*/
char		**ft_get_cub(const char *path);

/*	Parsing/ft_parse_data.c	*/
t_data		*ft_parse_data(char **identifiers, char **map);
char		*search_texture_path(char *identifier, char **data);

/*	Parsing/ft_get_rgb_from_id.c	*/
int			ft_get_rgb_from_id(char *id, char **data);

/*	Parsing/ft_parsing_main.c	*/
t_data		*ft_parsing_main(char *path);

/*	Parsing/ft_map_parsing.	*/
char		**ft_parse_map(char **src);

/*	Parsing/ft_parse_player.c	*/
t_player	*ft_parse_player(char	**map);

/*	Mlx/key_hook.c	*/
void		handle_key_hook(mlx_key_data_t keydata, void *param);

/* ft_printing.c */
// void	ft_print_lines_v3(t_data *data, t_fvector start,t_fvector end, mlx_texture_t *text, int text_pos);
// void	ft_print_lines_v3(t_data *data, int x, int drawStart, int drawEnd, int color);
void	ft_print_lines_v3(mlx_image_t *img, int x, int drawStart, int drawEnd, int color);

/* ft_raycast_utils.c */
float		deg_to_rad(int angle);
float		dist(t_fvector a, t_fvector b, float angle);
int			fix_ang(int angle);

/* ft_raycast.c */
void		ft_draw_ray3d(t_data *data);

/* ft_draw.c */
mlx_texture_t *ft_get_texture(t_data *data, const t_fvector ray_pos, int *text_x);
mlx_image_t	*ft_draw_map(t_data *data);
void		ft_draw_case(mlx_image_t *img, t_ivector pos, int color);
void		ft_draw_3D(mlx_image_t *img, float ax, float ay, float bx, float by, int color);
void	ft_draw_3D_2(t_data *data, t_fvector start, t_fvector end, mlx_texture_t *text, int text_pos);
void		draw_line(mlx_image_t *img, int beginX, int beginY, int endX, int endY, int color);

/* main.c */

void		ft_clean_img(mlx_image_t *img_ray);
mlx_image_t	*fill_image(int color, size_t x, size_t y, mlx_t *mlx);

#endif
