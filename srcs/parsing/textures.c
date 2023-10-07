/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:45 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/07 15:39:37 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
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
	int		len;
	int		fd;
	char	*trim;

	trim = ft_strtrim(&path[2], " \t");
	len = ft_strlen(trim);
	if (len < 4 || ft_strncmp(&trim[len - 4], ".png", 4) != 0)
	{
		free(trim);
		return (0);
	}
	fd = open(trim, O_RDONLY);
	free(trim);
	return (fd != -1);
}

static void	assign(mlx_texture_t **a, char *b)
{
	char	*trim;

	if ((*a) != NULL)
		mlx_delete_texture(*a);
	trim = ft_strtrim(b, " \t");
	(*a) = mlx_load_png(trim);
	free(trim);
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
