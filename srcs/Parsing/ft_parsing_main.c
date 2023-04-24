/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:45:20 by mjuin             #+#    #+#             */
/*   Updated: 2023/04/24 09:43:52 by mjuin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_get_sep_line(char **id)
{
	size_t	pos;
	size_t	lpos;

	pos = 0;
	while (id[pos] != NULL)
	{
		lpos = 0;
		while (id[pos][lpos] != '\0' && id[pos][lpos] == ' ')
			lpos++;
		if (id[pos][lpos] == '1')
			return (pos);
		pos++;
	}
	return (-1);
}

char	**ft_get_map_part(char **src)
{
	int		sep;
	char	**mapped;
	size_t	pos;

	sep = ft_get_sep_line(src);
	if (sep == -1)
	{
		ft_print_error("No map part found in .cub");
		return (NULL);
	}
	pos = 0;
	while (src[sep + pos] != NULL)
		pos++;
	mapped = malloc((pos + 1) * sizeof(char *));
	if (mapped == NULL)
		return (NULL);
	pos = 0;
	while (src[sep + pos] != NULL)
	{
		mapped[pos] = ft_strdup(src[sep + pos]);
		pos++;
	}
	mapped[pos] = NULL;
	return (mapped);
}

static char	**ft_get_id_part(char **src)
{
	int		sep;
	char	**id;

	sep = ft_get_sep_line(src);
	if (sep == -1)
		return (NULL);
	id = malloc((sep) * sizeof(char *));
	if (id == NULL)
		return (NULL);
	id[sep - 1] = NULL;
	sep--;
	while (sep > 0)
	{
		id[sep - 1] = ft_strdup(src[sep - 1]);
		sep--;
	}
	ft_double_free(src);
	return (id);
}

t_data	*ft_parsing_main(char *path)
{
	char		**identifiers;
	char		**mapped;
	t_data		*data;

	identifiers = ft_get_cub(path);
	mapped = ft_get_map_part(identifiers);
	identifiers = ft_get_id_part(identifiers);
	data = ft_parse_data(identifiers, mapped);
	ft_double_free(identifiers);
	ft_double_free(mapped);
	if (mapped == NULL || identifiers == NULL || data == NULL)
		ft_exit("Error on malloc", 1);
	ft_check_map(data);
	return (data);
}
