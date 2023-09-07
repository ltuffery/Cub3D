/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:21:55 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/07 09:28:28 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static int	is_good_color_format(char *colors_line)
{
	int	i;
	int	nb_comma;

	i = 0;
	nb_comma = 0;
	while (colors_line[i] != '\0')
	{
		if (!ft_isdigit(colors_line[i]) && colors_line[i] != ',')
			return (0);
		if (colors_line[i] == ',')
			nb_comma++;
		i++;
	}
	return (nb_comma == 2);
}

int	is_color_line(char *line)
{
	if (line[0] != FLOOR && line[0] != CEILING && line[1] != ' ')
		return (0);
	if (!is_good_color_format(&line[2]))
		return (0);
	return (1);
}

void	colors_handler()
{
}
