/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:45 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/06 12:44:46 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static void	error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

static void	valid_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return ;
	if (ft_strncmp(line, "SO ", 3) == 0)
		return ;
	if (ft_strncmp(line, "WE ", 3) == 0)
		return ;
	if (ft_strncmp(line, "EA ", 3) == 0)
		return ;
	error("Invalid identifier");
}

static void	valid_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error("Invalid path");
	close(fd);
}

void	textures_handler(int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		valid_identifier(line);
		line[ft_strlen(line) - 1] = '\0';
		valid_path(&line[3]);
		i++;
	}
}
