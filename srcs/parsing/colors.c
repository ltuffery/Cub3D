/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:21:55 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/09 16:38:21 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <stdio.h>

static int	is_good_color_format(char *colors_line)
{
	int	i;
	int	nb_comma;
	int	find_nb;

	i = 0;
	nb_comma = 0;
	find_nb = 0;
	while (colors_line[i] != '\0')
	{
		if (!ft_isdigit(colors_line[i]) && colors_line[i] != ',')
			return (0);
		if (colors_line[i] == ',' && find_nb == 0)
			return (0);
		if (colors_line[i] == ',')
		{
			find_nb = 0;
			nb_comma++;
		}
		else if (ft_isdigit(colors_line[i]))
			find_nb++;
		i++;
	}
	return (nb_comma == 2 && find_nb != 0);
}

int	is_color_line(t_map **map, char *line)
{
	char	*trim;

	if ((line[0] != FLOOR && line[0] != CEILING) || line[1] != ' ')
		return (0);
	trim = ft_strtrim(&line[2], " \t");
	if (!is_good_color_format(trim))
	{
		(*map)->error = 1;
		free(trim);
		return (0);
	}
	free(trim);
	return (1);
}

static void	free_tab_and_more(char **tab, char *more)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	free(more);
}

void	create_color(t_color **clr, unsigned int color)
{
	if (*clr == NULL)
		*clr = malloc(sizeof(t_color));
	if (*clr == NULL)
		return ;
	(*clr)->color = color;
	(*clr)->find = 1;
}

void	insert_color(t_map **map, char *line)
{
	char			**split;
	unsigned int	color;
	int				i;
	int				nbr;
	char			*trim;

	trim = ft_strtrim(&line[2], " \t");
	split = ft_split(trim, ',');
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
		create_color(&(*map)->floor, color);
	else
		create_color(&(*map)->ceiling, color);
	free_tab_and_more(split, trim);
}
