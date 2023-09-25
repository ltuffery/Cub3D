/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:26:27 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/25 15:48:37 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

/*static int	is_wall(int player_y, int player_x, char **map)
{
	return (map[player_y][player_x] == '1');
}*/

void	move_forward(t_data *data)
{
	float	tmpx;
	float	tmpy;

	tmpx = data->player->x + SPEED * cosf(data->player->direction);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * sinf(data->player->direction);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

void	move_back(t_data *data)
{
	float	tmpx;
	float	tmpy;

	tmpx = data->player->x - SPEED * cosf(data->player->direction);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y - SPEED * sinf(data->player->direction);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

void	move_rigth(t_data *data)
{
	float	tmpx;
	float	tmpy;

	tmpx = data->player->x + SPEED * cosf(data->player->direction + 90);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * sinf(data->player->direction + 90);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

void	move_left(t_data *data)
{
	float	tmpx;
	float	tmpy;

	tmpx = data->player->x - SPEED * cosf(data->player->direction + 90);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y - SPEED * sinf(data->player->direction + 90);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}
