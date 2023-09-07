/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:27:12 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/07 10:42:04 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"

void	setup_config(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line != NULL)
	{
		if (is_texture_line(line))
			insert_texture(map, line);
		line = get_next_line(map->fd);
	}
}
