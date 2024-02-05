/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:09:47 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/21 11:12:48 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_print_error(char *message)
{
	static int	printed;

	if (printed == 0)
	{
		ft_printf_fd(2, "%s\n", "Error");
		ft_printf_fd(2, "%s\n", message);
		printed = 1;
	}
}

void	ft_exit(char *message, int exit_code)
{
	if (exit_code == 0)
	{
		if (message != NULL)
			ft_printf_fd(1, message);
		exit(0);
	}
	if (message != NULL)
		ft_print_error(message);
	exit(exit_code);
}
