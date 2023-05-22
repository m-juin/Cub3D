/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:28:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/22 16:11:09 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/include/libft.h"
# include "../../libft/include/get_next_line.h"
# include "../../MLX42/include/MLX42/MLX42.h"
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

# define WIDTH	1280
# define HEIGHT	720
# define CSIZE	64

/* Minimap defines */

# define MAP_CSIZE 32
# define RAD 0.01745329251
# define ROT 0.08726646259

typedef struct s_ivector	t_ivector;
typedef struct s_dvector	t_dvector;
typedef struct s_fvector	t_fvector;
typedef struct s_pixel		t_pixel;
typedef struct s_door		t_door;
typedef struct s_player		t_player;
typedef struct s_data		t_data;
typedef struct s_bresenham	t_bresenham;
typedef struct s_minimap	t_minimap;
typedef struct s_calc_data	t_calc_data;
typedef struct s_draw_data	t_draw_data;
typedef struct s_cursor		t_cursor;

enum	e_dir
{
	north = 0,
	south = 2,
	east = 1,
	west = 3,
};

struct s_ivector
{
	int	x;
	int	y;
};

struct s_dvector
{
	double	x;
	double	y;
};

struct s_fvector
{
	float	x;
	float	y;
};

struct s_pixel
{
	int	color;
	int	state;
};

struct s_door
{
	t_ivector		map_pos;
	mlx_texture_t	**animation;
	int				anim_state;
	int				anim_count;
	int				anim_speed;
	int				speed_count;
};


struct s_player
{
	t_dvector	map_pos;
	t_fvector	player_center;
	t_fvector	minimap_pos;
	t_fvector	minimap_offset;
	t_dvector	target_pos;
	enum e_dir	target_dir;
	enum e_dir	facing_dir;
	t_fvector	pos;
	t_dvector	dir;
	t_dvector	plane;
	mlx_image_t	*img;
	bool		canmove;
	int			player_angle;
};

struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img_ray;
	mlx_image_t		*img_3d;
	mlx_image_t		*img_map;
	t_player		*player;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*door;
	mlx_texture_t	**animation;
	t_door			**door_list;
	t_ivector		msize;
	t_cursor		*cursor;
	int				ground;
	int				top;
	char			**map;
};

struct s_bresenham 
{
	t_ivector	pos1;
	t_ivector	pos2;
	t_ivector	incr;
	t_fvector	error;
	t_fvector	delta;
};

struct s_minimap
{
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector	side;
	t_ivector	map;
	float		dist;
	float		tan;
	float		ray_angle;
	int			offset;
};

struct s_calc_data
{
	double		walldist;
	t_ivector	map;
	t_dvector	side_dist;
	t_dvector	delta_dist;
};

struct s_draw_data
{
	t_ivector		pos;
	mlx_texture_t	*text;
	int				lineh;
	int				width_pos;
	int				side;
};

struct s_cursor
{
	t_ivector	prev_pos;
	enum e_dir	side;
};


/*	Utils/exit_bonus.c	*/
void		ft_exit(char *message, int exit_code);
void		ft_print_error(char *message);

/*	Utils/free_bonus.c	*/
void		*ft_double_free(char **array);
void		ft_free_map_data(t_data *data);
void		ft_free_data(t_data *data);

/*	Utils/colors_bonus.c	*/
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

/*	Utils/count_door_bonus.c	*/
int			ft_count_door(char **map);

/*	Utils/empty_line_bonus.c	*/
int			ft_check_identifier_empty_line(char **id);
int			ft_line_is_empty(char *line);

/*	Parsing/ft_checkarg_bonus.c	*/
void		ft_checkarg(int ac, char **av);
int			ft_try_open(const char *path);

/*	Parsing/ft_checkmap_bonus.c	*/
void		ft_check_map(t_data *data);

/*	Parsing/ft_get_cub_bonus.c	*/
char		**ft_get_cub(const char *path);

/*	Parsing/ft_parse_data_bonus.c	*/
t_data		*ft_parse_data(char **identifiers, char **map);
char		*search_texture_path(char *identifier, char **data);

/*	Parsing/ft_get_rgb_from_id_bonus.c	*/
int			ft_get_rgb_from_id(char *id, char **data);

/*	Parsing/ft_parsing_main_bonus.c	*/
t_data		*ft_parsing_main(char *path);

/*	Parsing/ft_map_parsing_bonus.c	*/
char		**ft_parse_map(char **src);

/*	Parsing/ft_parse_player_bonus.c	*/
t_player	*ft_parse_player(char	**map);
void		ft_get_rotation(enum e_dir start_dir, t_player *player);

/*	Parsing/ft_load_animation_bonus.c	*/
mlx_texture_t	**ft_load_animation();

/*	Parsing/ft_parse_door_bonus.c	*/
t_door 		**ft_parse_door(t_data *data);

/*	Mlx/key_hook_bonus.c	*/
void		handle_key_hook(mlx_key_data_t keydata, void *param);

/*	Mlx/mouse_hook_bonus.c	*/
void		rotation_hook(mlx_key_data_t keydata, t_player *pl);
void    	cursor_hook(double x, double y, void *param);

/* Mlx/manage_collision_bonus.c */
t_dvector	collide(t_player *player, t_data *data, mlx_key_data_t keydata);

/* ft_raycast_bonus.c */
void		ft_draw_ray3d(t_data *data);

/* Utils/ft_raycast_get_bonus.c */
t_dvector	ft_get_delta(t_dvector raydir);
void		ft_get_texture(t_data *data, t_draw_data *draw, t_calc_data *calc);
int			ft_get_textx(t_data *data, t_dvector raydir, t_draw_data draw, double wall);
t_ivector	ft_get_step(t_dvector raydir);
t_dvector	ft_get_sided(t_dvector raydir, t_ivector map, t_dvector pl, t_dvector delta);

/*	ft_draw_column_bonus.c	*/
void		ft_draw_column(t_data *data, t_draw_data draw, int textx);

/*	Utils/ft_draw_column_utils_bonus.c	*/
bool		to_redraw(int x, int y, int color, mlx_image_t *img);
int			get_color(int x, int y, mlx_texture_t *text);
t_ivector	get_draw_data(int lineh, mlx_image_t *img);

/*	Utils/door_utils_bonus	*/
t_door	*ft_get_door(t_ivector map_pos, t_door **doors);
void	ft_update_doors(t_door **door_list, t_data *data);

/* ft_draw_minimap_bonus.c */
void		ft_draw_case(mlx_image_t *img, t_ivector pos, int color);
void		ft_draw_minimap(mlx_image_t *map, t_data *data);
int			fix_ang(int angle);

/* main_bonus.c */
void		ft_clean_img(mlx_image_t *img_ray);
mlx_image_t	*fill_image(int color, size_t x, size_t y, mlx_t *mlx);

/* ft_move_bonus.c */
bool		ft_move(t_data *data);

/* ft_rotate_bonus.c */
bool		ft_rotate(t_data *data);

/* Minimap/ft_fov_utils_bonus.c */
void		ft_vertical_rays(t_data *data, t_minimap *map);
void		ft_vertical_rays_bis(t_data *data, t_minimap *map);
void		ft_horizontal_rays(t_data *data, t_minimap *map);
void		ft_horizontal_rays_bis(t_data *data, t_minimap *map);

/* Minimap/ft_printing_bonus.c */
void		ft_print_lines(mlx_image_t *img, t_data *data, t_fvector ray_pos);

/* Minimap/minimap_bonus.c */
void		ft_draw_ray_minimap(t_data *data);
float		deg_to_rad(int angle);
float		dist(t_fvector a, t_fvector b, float angle);
int			fix_ang(int angle);

#endif
