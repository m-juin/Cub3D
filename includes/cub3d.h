/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:28:08 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/19 16:36:46 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>

/* Window defines */

# define WIDTH 1920
# define HEIGHT 1080

/* Raycasting defines */

# define PI 3.141592653589793238462643383279502884197

typedef struct s_map_data
{
	char	*text_north;
	char	*text_south;
	char	*text_east;
	char	*text_west;
	char	*text_ground;
	char	*text_ceiling;
}	t_map_data;

/*	Utils/free.c	*/

void		*ft_simple_free(void *arg);
void		*ft_double_free(char **array);
void		free_map_data(t_map_data *data);

/*	Utils/check.c	*/
void		ft_checkmap_path(char *map_path);
void		ft_checkarg(int ac, char **av);
void		ft_checkmap_empty(int fd);

/*	Utils/exit.c	*/
void		ft_exit(char *message, int exitcode);

/*	Map/mapget.c	*/
t_map_data	*ft_mapget_content(char *map_path);

/*	Map/mapcount	*/
int			ft_mapcount_line(int fd);

/*	Utils/map.c	*/
void		ft_fill_map_array(int fd, char **map, int lcount);
int			ft_map_open(char *map_path);

#endif
