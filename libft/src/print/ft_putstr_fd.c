/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:14:03 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/17 11:20:24 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	size;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	size = ft_strlen(s);
	write(fd, s, size);
	return (size);
}
