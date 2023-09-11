/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:13:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/11 11:58:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>

static void	valid_number_argv(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nOnly 2 args required\n", 2);
		exit(1);
	}
}

static void	valid_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid extension", 2);
		exit(1);
	}
}

static void	clean_map(t_map *map)
{
	if (map->no != NULL)
		free(map->no);
	if (map->we != NULL)
		free(map->we);
	if (map->ea != NULL)
		free(map->ea);
	if (map->so != NULL)
		free(map->so);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	t_map	map;

	valid_number_argv(ac);
	valid_extension(av[1]);
	ft_bzero(&map, sizeof(map));
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	setup_config(&map);
	printf("%s | %s | %s | %s\n%u | %u\n", map.ea, map.no, map.so, map.we, map.ceiling, map.floor);
	if (map.ea == NULL || map.no == NULL || map.so == NULL || map.we == NULL)
	{
		ft_putendl_fd("Error", 2);
		clean_map(&map);
		return (1);
	}
	clean_map(&map);
	close(map.fd);
}
