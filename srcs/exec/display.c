/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/20 17:39:14 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <math.h>

static void	puts_pixel(mlx_image_t *image, int y, int x, int type_chunk)
{
	int	xx;
	int	yy;
	int	d;

	yy = 0;
	if (type_chunk == 1)
	d = 10;
	else
		d = 15;
	while (yy < d)
	{
		xx = 0;
		while (xx < d)
		{
			if (type_chunk == 0)
				mlx_put_pixel(image, xx + (x * d), yy + (y * d), 0xFFFFFFFF);
			else
				mlx_put_pixel(image, xx + (x * d), yy + (y * d), 0x00FF00FF);
			xx++;
		}
		yy++;
	}
}

static void	display_player_view(t_player *player, t_data *data)
{
	t_player	inc;
	t_player	copy;
	float		dx;
	float		dy;
	float		steps;

	dx = (player->x * 15) - (cosf(player->direction) + 15);
	dy = (player->y * 15) - (sinf(player->direction) + 15);
	steps = fmax(fabs(dx), fabs(dy));
	inc.x = dx / (float)steps;
	inc.y = dy / (float)steps;
	copy.x = player->x;
	copy.y = player->y;
	while (steps >= 0)
	{
		steps--;
		if (copy.x >= 0 && copy.x <= WIDTH)
			if (copy.y >= 0 && copy.y <= HEIGHT)
				mlx_put_pixel(data->image, (int)copy.x, (int)copy.y, 0x0000FFFF);
		copy.x += inc.x;
		copy.y += inc.y;
	}
}

void	display_player(t_data *data)
{
	int	xx;
	int	yy;
	int	d;

	yy = 0;
	d = 10;
	while (yy < d)
	{
		xx = 0;
		while (xx < d)
		{
			mlx_put_pixel(data->image, xx + data->player->x * 15 - 5, \
					yy + data->player->y * 15 - 5, 0xFF0000FF);
			xx++;
		}
		yy++;
	}
	display_player_view(data->player, data);
}

void	display_map(t_data *data)
{
	int			y;
	int			x;

	y = 0;
	while (data->map->content[y] != NULL)
	{
		x = 0;
		while (data->map->content[y][x] != '\0')
		{
			if (data->map->content[y][x] == '1')
				puts_pixel(data->image, y, x, 0);
			else
				puts_pixel(data->image, y, x, 2);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
