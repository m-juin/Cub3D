/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:09:50 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/17 11:29:31 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}*/

void	ft_exit(char *message, int exitcode)
{
	if (exitcode == 0)
		ft_printf_fd(1, "%s\n", message);
	else
		ft_printf_fd(2, "%s\n", message);
	exit(exitcode);
}
