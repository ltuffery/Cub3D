/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:39:42 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/07 19:04:06 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int	check_valid_border(char **content, int y, int x)
{
	int	i;

	i = -1;
	while (i < 2)
	{
		if (content[y][x] == ' ')
			return (1);
		if (y == 0 || x == 0)
			return (0);
		if (content[y - 1][x] == ' ' || content[y - 1][x] == '\0')
			return (0);
		if (content[y][x + i] == ' ' || content[y][x + i] == '\0')
			return (0);
		if (content[y + 1] == NULL)
			return (0);
		if (content[y + 1][x] == ' ' || content[y + 1][x] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map(char **content)
{
	int			i;
	int			j;
	int			nb_player_location;

	i = 0;
	nb_player_location = 0;
	while (content[i] != NULL)
	{
		j = 0;
		while (content[i][j] != '\0')
		{
			if (content[i][j] == '0' && (i == 0 || content[i + 1] == NULL))
				return (0);
			else if (content[i][j] != '1' && !check_valid_border(content, i, j))
				return (0);
			else if (ft_strchr("NSEW", content[i][j]) != 0)
				nb_player_location++;
			j++;
		}
		i++;
	}
	return (nb_player_location == 1);
}

int	is_map_line(char *line)
{
	int	i;
	int	is_full_space;

	i = 0;
	is_full_space = 1;
	while (line[i] != '\0')
	{
		if (ft_strchr("01NSEW ", line[i]) == 0)
			return (0);
		if (line[i] != ' ')
			is_full_space = 0;
		i++;
	}
	return (is_full_space == 0);
}

static void	fill_map(char **content)
{
	int		i;
	size_t	max_len;
	char	*new_line;

	max_len = find_max_len(content);
	i = 0;
	while (content[i] != NULL)
	{
		if (max_len == ft_strlen(content[i]))
		{
			i++;
			continue ;
		}
		new_line = ft_calloc(max_len, sizeof(char *));
		if (new_line == NULL)
			continue ;
		ft_strlcpy(new_line, content[i], ft_strlen(content[i]) + 1);
		free(content[i]);
		content[i] = fill_str(new_line, ' ', max_len);
		i++;
	}
}

void	insert_map(t_map **map, char *line)
{
	(*map)->content = ft_strappend(line, (*map)->content);
	line = get_next_line((*map)->fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1 == '\n'])
			line[ft_strlen(line) - 1] = '\0';
		if (!is_map_line(line))
			break ;
		(*map)->content = ft_strappend(line, (*map)->content);
		free(line);
		line = get_next_line((*map)->fd);
	}
	free(line);
	fill_map((*map)->content);
}
