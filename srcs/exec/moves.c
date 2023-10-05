/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:26:27 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/05 19:42:07 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>
#include <stdbool.h>

static float	d_colision(float rad, bool cos)
{
	if (cos)
		return (0.3 * cosf(rad));
	return (0.3 * sinf(rad));
}

void	move(t_data *data, int pos1, int pos2)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x + SPEED * pos1 * cosf(rad);
	if (data->map->content[(int)(data->player->y + d_colision(rad, false) * pos2)][(int)(tmpx + d_colision(rad, true) * pos1)] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * pos2 * sinf(rad);
	if (data->map->content[(int)(tmpy + d_colision(rad, false) * pos2)][(int)(data->player->x + d_colision(rad, true) * pos1)] != '1')
		data->player->y = tmpy;
}

void	move_forward(t_data *data)
{
	move(data, 1, 1);
}

void	move_back(t_data *data)
{
	move(data, -1, -1);
}

#define TRUC 67.5

void	move_rigth(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x - SPEED * cosf(rad - PI / 2);
	if (data->map->content[(int)(data->player->y - d_colision(rad, false))][(int)(tmpx - d_colision(rad, true))] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y - SPEED * sinf(rad - PI / 2);
	if (data->map->content[(int)(tmpy - d_colision(rad, false))][(int)(data->player->x - d_colision(rad, true))] != '1')
		data->player->y = tmpy;
}

void	move_left(t_data *data)
{
	float	tmpx;
	float	tmpy;
	float	rad;

	rad = data->player->direction->degree * PI / 180;
	tmpx = data->player->x + SPEED * cosf(rad - PI / 2);
	if (data->map->content[(int)(data->player->y + d_colision(rad, false))][(int)(tmpx + d_colision(rad, true))] != '1')
		data->player->x = tmpx;
	tmpy = data->player->y + SPEED * sinf(rad - PI / 2);
	if (data->map->content[(int)(tmpy + d_colision(rad, false))][(int)(data->player->x + d_colision(rad, true))] != '1')
		data->player->y = tmpy;
}
