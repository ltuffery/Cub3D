/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:13:23 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/06 10:48:12 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static void	valid_number_argv(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Only 2 args required\n", 2);
		exit(1);
	}
}

static void	valid_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Invalid extension", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	valid_number_argv(ac);
	valid_extension(av[1]);
}
