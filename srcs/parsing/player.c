/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:02:24 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/22 11:54:23 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdlib.h>

static void	insert_direction(t_player *player, t_map **map, int i, int j)
{
	if ((*map)->content[i][j] == 'N')
		player->direction = 90;
	else if ((*map)->content[i][j] == 'S')
		player->direction = 270;
	else if ((*map)->content[i][j] == 'W')
		player->direction = 180;
	else
		player->direction = 0;
	player->y = i + 0.5;
	player->x = j + 0.5;
}

void	set_player(t_map **map)
{
	int			i;
	int			j;
	t_player	*player;

	i = 0;
	player = malloc(sizeof(t_player) * 1);
	if (player == NULL)
		return ;
	while ((*map)->content[i] != NULL)
	{
		j = 0;
		while ((*map)->content[i][j] != '\0')
		{
			insert_direction(player, map, i, j);
			if (player->direction != '\0')
				break ;
			j++;
		}
		if (player->direction != '\0')
			break ;
		i++;
	}
	(*map)->player = player;
}
