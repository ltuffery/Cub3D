/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:26:27 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/26 11:57:46 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	move_forward(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x + SPEED * cosf(rad);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * sinf(rad);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

void	move_back(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x - SPEED * cosf(rad);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y - SPEED * sinf(rad);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

#define TRUC 67.5

void	move_rigth(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x + SPEED * cosf(rad);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * sinf(rad);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}

void	move_left(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x - SPEED * cosf(rad);
	if (data->map->content[(int)data->player->y][(int)tmpx] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y - SPEED * sinf(rad);
	if (data->map->content[(int)tmpy][(int)data->player->x] != '1')
		data->player->y = tmpy;
}
