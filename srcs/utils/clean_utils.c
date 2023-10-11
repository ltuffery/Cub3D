/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:37:49 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/11 16:45:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub.h"
#include <stdlib.h>

static void	clean_player(t_player *player)
{
	if (player == NULL)
		return ;
	if (player->direction != NULL)
		free(player->direction);
	free(player);
}

static void	clean_color(t_color *color)
{
	if (color != NULL)
		free(color);
}

void	clean_map(t_map *map)
{
	int	i;

	if (map->no != NULL)
		mlx_delete_texture(map->no);
	if (map->we != NULL)
		mlx_delete_texture(map->we);
	if (map->ea != NULL)
		mlx_delete_texture(map->ea);
	if (map->so != NULL)
		mlx_delete_texture(map->so);
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
	clean_color(map->ceiling);
	clean_color(map->floor);
	clean_player(map->player);
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
}
