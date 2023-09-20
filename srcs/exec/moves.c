/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:26:27 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/20 17:00:44 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_wall(int player_y, int player_x, char **map)
{
	return (map[player_y][player_x] == '1');
}

void	move_forward(t_data *data)
{
	if (!is_wall(data->player->y - SPEED, data->player->x, data->map->content))
		data->player->y -= SPEED;
}

void	move_back(t_data *data)
{
	if (!is_wall(data->player->y + SPEED, data->player->x, data->map->content))
		data->player->y += SPEED;
}

void	move_rigth(t_data *data)
{
	if (!is_wall(data->player->y, data->player->x + SPEED, data->map->content))
		data->player->x += SPEED;
}

void	move_left(t_data *data)
{
	if (!is_wall(data->player->y, data->player->x - SPEED, data->map->content))
		data->player->x -= SPEED;
}
