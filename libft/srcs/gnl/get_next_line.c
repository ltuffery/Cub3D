/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:05:59 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/06 11:13:39 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*my_read_line(int fd, char *str)
{
	char	*buffer;
	int		read_status;

	read_status = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	while (my_strchr(buffer, '\n') == 0 && read_status != 0)
	{
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1)
		{
			if (str != NULL)
				free(str);
			free(buffer);
			return (NULL);
		}
		buffer[read_status] = '\0';
		str = my_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*my_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	my_strlcpy(line, str, i + 1);
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = my_read_line(fd, str);
	if (str == NULL)
		return (NULL);
	line = my_get_line(str);
	str = my_substr(str);
	return (line);
}
