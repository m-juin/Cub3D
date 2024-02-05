/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:41:34 by mjuin             #+#    #+#             */
/*   Updated: 2023/05/23 14:52:51 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_free_strtrim(char *str, char const *charset)
{
	char	*tmp;

	if (str == NULL)
		return (NULL);
	tmp = ft_strtrim(str, charset);
	free(str);
	return (tmp);
}
