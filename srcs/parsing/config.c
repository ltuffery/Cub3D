/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:27:12 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/11 18:09:46 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "libft.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	setup_config(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line != NULL && map->error == 0)
	{
		line[ft_strlen(line) - 1] = '\0';
		if (!is_empty_line(line) && is_texture_line(line))
			insert_texture(&map, line);
		else if (!is_empty_line(line) && is_color_line(&map, line))
			insert_color(&map, line);
		else if (!is_empty_line(line) && is_map_line(line))
		{
			insert_map(&map, line);
			set_player(&map);
			break ;
		}
		if (line != NULL)
			free(line);
		line = get_next_line(map->fd);
	}
	if (line != NULL)
		free(line);
}
