/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:45 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/07 11:02:35 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static int	valid_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

static int	valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	return (fd != -1);
}

int	is_texture_line(char *line)
{
	return (valid_path(line) && valid_identifier(line));
}

void	insert_textures(t_map *map, char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strncmp(line, "NO", 2) == 0)
		map->no = ft_strdup(&line[3]);
	else if (ft_strncmp(line, "SO", 2) == 0)
		map->so = ft_strdup(&line[3]);
	else if (ft_strncmp(line, "WE", 2) == 0)
		map->we = ft_strdup(&line[3]);
	else
		map->ea = ft_strdup(&line[3]);
}
