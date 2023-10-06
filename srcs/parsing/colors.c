/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:21:55 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/06 18:42:17 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

#include <stdio.h>
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
	if ((line[0] != FLOOR && line[0] != CEILING) || line[1] != ' ')
		return (0);
	if (!is_good_color_format(&line[2]))
		return (0);
	return (1);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	insert_color(t_map **map, char *line)
{
	char			**split;
	unsigned int	color;
	int				i;
	int				nbr;

	split = ft_split(&line[2], ',');
	color = 0;
	i = 0;
	while (split[i] != NULL && (*map)->error == 0)
	{
		nbr = ft_atoi(split[i]);
		if (nbr > 255 || nbr < 0)
			(*map)->error = 1;
		color |= nbr << (8 * (4 - (i + 1)));
		i++;
	}
	color |= 0xFF;
	if (line[0] == FLOOR)
		(*map)->floor = color;
	else
		(*map)->ceiling = color;
	free_tab(split);
}
