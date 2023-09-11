/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:27:12 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/11 11:06:57 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "libft.h"

void	setup_config(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line != NULL)
	{
		line[ft_strlen(line) - 1] = '\0';
		if (is_texture_line(line))
			insert_texture(&map, line);
		else if (is_color_line(line))
			insert_color(&map, line);
		free(line);
		line = get_next_line(map->fd);
	}
	if (line != NULL)
		free(line);
}
