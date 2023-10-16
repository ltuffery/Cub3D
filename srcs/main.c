/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:13:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/16 15:47:34 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void	valid_number_argv(int ac)
{
	if (ac != 2)
	{
		ft_putendl_fd("Error\nInvalid number of arguments", 2);
		ft_putendl_fd("Usage : ./cub3D < insert map path>", 2);
		exit(1);
	}
}

static void	valid_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4) != 0)
	{
		ft_putendl_fd("Error\nInvalid extension", 2);
		exit(1);
	}
}

static int	is_all_good(t_map *map)
{
	if (map->error == 1 || map->ceiling == NULL || map->floor == NULL)
	{
		ft_putendl_fd("Error\nInvalid color", 2);
		return (0);
	}
	if (map->ea == NULL || map->no == NULL || \
			map->so == NULL || map->we == NULL)
	{
		ft_putendl_fd("Error\nInvalid texture", 2);
		return (0);
	}
	if (map->content == NULL || !is_valid_map(map->content))
	{
		ft_putendl_fd("Error\nInvalid map", 2);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_map	map;

	valid_number_argv(ac);
	valid_extension(av[1]);
	ft_bzero(&map, sizeof(map));
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
	{
		ft_putendl_fd("Error\nInvalid fd", 2);
		exit(1);
	}
	setup_config(&map);
	if (!is_all_good(&map))
	{
		clean_map(&map);
		close(map.fd);
		return (1);
	}
	launcher(&map);
	close(map.fd);
}
