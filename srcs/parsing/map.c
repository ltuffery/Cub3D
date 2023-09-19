/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:39:42 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/19 15:56:08 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

static int	check_valid_border(char **content, int y, int x)
{
	int	i;

	i = -1;
	while (i < 2)
	{
		if (content[y - 1][x + i] == ' ')
			return (0);
		if (content[y][x + i] == ' ')
			return (0);
		if (content[y + 1][x + i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

void	set_player(t_map **map)
{
	int			i;
	int			j;
	t_player	*player;

	i = 0;
	player = malloc(sizeof(t_player) * 1);
	if (player == NULL)
		return ;
	while ((*map)->content[i] != NULL)
	{
		j = 0;
		while ((*map)->content[i][j] != '\0')
		{
			if ((*map)->content[i][j] == 'N')
				player->direction = 'N';
			if ((*map)->content[i][j] == 'S')
				player->direction = 'S';
			if ((*map)->content[i][j] == 'E')
				player->direction = 'E';
			if ((*map)->content[i][j] == 'W')
				player->direction = 'W';
			j++;
		}
		if (player->direction != '\0')
		{
			player->y = i;
			player->x = j;
			break ;
		}
		i++;
	}
	(*map)->player = player;
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
			else if (content[i][j] == '0' && !check_valid_border(content, i, j))
				return (0);
			else if (ft_strchr("NSEW", content[i][j]) != 0)
			{
				nb_player_location++;
				if (!check_valid_border(content, i, j))
					return (0);
			}
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
		line[ft_strlen(line) - 1] = '\0';
		if (!is_map_line(line))
			break ;
		(*map)->content = ft_strappend(line, (*map)->content);
		free(line);
		line = get_next_line((*map)->fd);
	}
	fill_map((*map)->content);
}
