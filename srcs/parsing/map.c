/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:39:42 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/13 12:04:26 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

int	is_valid_map(char **content)
{
	int	i;
	int	j;

	i = 0;
	while (content[i] != NULL)
	{
		j = 0;
		while (content[i][j] != '\0')
		{
		}
		i++;
	}
	return (1);
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

static size_t	find_max_len(char **content)
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

static void	fill_map(char **content)
{
	int		i;
	size_t	j;
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
		j = ft_strlen(content[i]);
		while (j < max_len)
		{
			new_line[j] = ' ';
			j++;
		}
		free(content[i]);
		content[i] = new_line;
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
