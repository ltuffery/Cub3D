/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/26 14:25:57 by ltuffery         ###   ########.fr       */
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
				mlx_put_pixel(image, xx + (x * d), yy + (y * d), 0x000000FF);
			xx++;
		}
		yy++;
	}
}

static int	colision(float x, float y, char **map)
{
	return (map[(int)y][(int)x] == '1');
}

static void	display_player_view(t_player *player, t_data *data, char shift)
{
    double longueur, dx, dy, x, y;

	longueur = 200;
    dx = (player->x + cosf((player->direction->degree + shift) * PI / 180) - player->x) / longueur;
    dy = (player->y + sinf((player->direction->degree + shift) * PI / 180) - player->y) / longueur;
    x = player->x;
    y = player->y;
	//int i = 1;
    while (!colision(x + dx, y, data->map->content) && !colision(x, y + dy, data->map->content)) {
        x += dx;
        y += dy;
		if (y > 0 && x > 0)
			mlx_put_pixel(data->image, x * 15, y * 15, 0x00FF00FF);
		//i++;
    }
}

void	display_player(t_data *data)
{
	int		xx;
	int		yy;
	int		d;
	float	shift;

	yy = 0;
	d = 10;
	shift = 0;
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
	while (shift < 60)
	{
		display_player_view(data->player, data, shift - 30);
		shift += 60.0 / WIDTH;
	}
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
}
