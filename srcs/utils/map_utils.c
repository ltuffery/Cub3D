/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:09:31 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/13 12:18:57 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	find_max_len(char **content)
{
	int		i;
	size_t	len;
	size_t	max_len;

	i = 0;
	max_len = 0;
	while (content[i] != NULL)
	{
		len = ft_strlen(content[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

char	*fill_str(char *str, char fill, size_t max)
{
	size_t	i;

	if (str == NULL)
		return (str);
	i = ft_strlen(str);
	while (i < max)
	{
		str[i] = fill;
		i++;
	}
	return (str);
}
