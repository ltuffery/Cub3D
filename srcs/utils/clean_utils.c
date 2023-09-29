/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:37:49 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/29 17:28:14 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdlib.h>

void	clean_map(t_map *map)
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
}

void	clean_rays(t_data *data)
{
	int	i;

	i = 0;
	while (data->rays[i] != NULL)
	{
		free(data->rays[i]);
		data->rays[i] = NULL;
		i++;
	}
}

void	clean_data(t_data *data)
{
	clean_map(data->map);
	clean_rays(data);
	free(data->player->direction);
	free(data->player);
}
