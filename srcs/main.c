/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:13:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/06 12:16:28 by ltuffery         ###   ########.fr       */
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
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid extension", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	int	fd;

	valid_number_argv(ac);
	valid_extension(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	textures_handler(fd);
}
