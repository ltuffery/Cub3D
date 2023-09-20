/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:13:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/20 16:50:24 by ltuffery         ###   ########.fr       */
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
	int	i;

	if (map->no != NULL)
		free(map->no);
	if (map->we != NULL)
		free(map->we);
	if (map->ea != NULL)
		free(map->ea);
	if (map->so != NULL)
		free(map->so);
	if (map->content != NULL)
	{
		i = 0;
		while (map->content[i] != NULL)
		{
			free(map->content[i]);
			i++;
		}
		free(map->content);
	}
	if (map->player != NULL)
		free(map->player);
}

static int	is_all_good(t_map *map)
{
	if (map->ea == NULL || map->no == NULL || \
			map->so == NULL || map->we == NULL)
		return (0);
	if (!is_valid_map(map->content))
		return (0);
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
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	setup_config(&map);
	if (!is_all_good(&map))
	{
		ft_putendl_fd("Error", 2);
		clean_map(&map);
		return (1);
	}
	launcher(&map);
	clean_map(&map);
	close(map.fd);
}
