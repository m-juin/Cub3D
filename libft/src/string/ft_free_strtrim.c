/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:41:34 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/19 09:44:03 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char *ft_free_strtrim(char *str, char const *charset)
{
	char	*tmp;

	if (str == NULL)
		return (NULL);
	tmp = ft_strtrim(str, charset);
	free(str);
	return (tmp);
}