/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:28:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/20 14:57:37 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h> 
# include <errno.h>

# define WIDTH 1920
# define HEIGHT 1080

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
	t_ivector 		map_pos;
	enum e_dir		facing_dir;
}	t_player;

/*	Utils/exit.c	*/
void	ft_exit(char *message, int exit_code);
void	ft_print_error(char *message);

/*	Utils/free.c	*/
void	*ft_double_free(char **array);
void	free_data(t_data *data);

/*	Utils/colors.c	*/
int		get_rgba(int r, int g, int b, int a);
int 	get_r(int rgba);
int 	get_g(int rgba);
int 	get_b(int rgba);
int 	get_a(int rgba);

/*	Parsing/ft_checkarg.c	*/
void	ft_checkarg(int ac, char **av);
int		ft_try_open(const char *path);

/*	Parsing/ft_checkmap.c	*/
void	ft_check_map(t_data *data);

/*	Parsing/ft_get_cub.c	*/
char	**ft_get_cub(const char *path);

/*	Parsing/ft_parse_data.c	*/
t_data	*ft_parse_data(char **identifiers, char **map);
char 	*search_texture_path(char *identifier, char **data);

/*	Parsing/ft_get_rgb_from_id.c	*/
int		ft_get_rgb_from_id(char *id, char **data);

/*	Parsing/ft_parsing_main.c	*/
void	ft_parsing_main(char *path);

#endif
