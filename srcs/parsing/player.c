/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:02:24 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/26 14:54:30 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdlib.h>

static void	insert_direction(t_player *player, t_map **map, int i, int j)
{
	player->direction->find = 1;
	if ((*map)->content[i][j] == 'N')
		player->direction->degree = 270;
	else if ((*map)->content[i][j] == 'S')
		player->direction->degree = 90;
	else if ((*map)->content[i][j] == 'W')
		player->direction->degree = 180;
	else if ((*map)->content[i][j] == 'E')
		player->direction->degree = 0;
	else
		player->direction->find = 0;
	if (player->direction->find)
	{
		player->y = i + 0.5;
		player->x = j + 0.5;
	}
}

void	set_player(t_map **map)
{
	int			i;
	int			j;
	t_player	*player;
	t_direction	*direction;

	i = 0;
	player = malloc(sizeof(t_player) * 1);
	if (player == NULL)
		return ;
	direction = malloc(sizeof(t_direction));
	if (direction == NULL)
		return ;
	player->direction = direction;
	while ((*map)->content[i] != NULL)
	{
		j = 0;
		while ((*map)->content[i][j] != '\0')
		{
			insert_direction(player, map, i, j);
			if (player->direction->find)
				break ;
			j++;
		}
		if (player->direction->find)
			break ;
		i++;
	}
	(*map)->player = player;
}
