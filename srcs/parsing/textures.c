/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:45 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/11 11:32:12 by ltuffery         ###   ########.fr       */
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
	int	len;
	int	fd;

	len  = ft_strlen(path) - 3;
	if (len < 4 || ft_strncmp(&path[len - 4], ".png", 4) != 0)
		return (0);
	fd = open(&path[3], O_RDONLY);
	return (fd != -1);
}

static void	assign(char **a, char *b)
{
	if ((*a) != NULL)
		free(*a);
	(*a) = ft_strdup(b);
}

int	is_texture_line(char *line)
{
	if (line[0] == '\0')
		return (0);
	return (valid_path(line) && valid_identifier(line));
}

void	insert_texture(t_map **map, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		assign(&(*map)->no, &line[3]);
	else if (ft_strncmp(line, "SO", 2) == 0)
		assign(&(*map)->so, &line[3]);
	else if (ft_strncmp(line, "WE", 2) == 0)
		assign(&(*map)->we, &line[3]);
	else if (ft_strncmp(line, "EA", 2) == 0)
		assign(&(*map)->ea, &line[3]);
}
