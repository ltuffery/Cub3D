/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/28 18:55:43 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

static t_ray	*display_player_view(t_player *player, t_data *data, char shift)
{
	t_vector	vec;
	t_ray		*ray;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	vec.x = (player->x + cosf((player->direction->degree + shift) * PI / 180) \
			- player->x) / LENGTH;
	vec.y = (player->y + sinf((player->direction->degree + shift) * PI / 180) \
			- player->y) / LENGTH;
	ray->x = player->x;
	ray->y = player->y;
	ray->len = 0;
	while (!colision(ray->x + vec.x, ray->y, data->map->content) && \
			!colision(ray->x, ray->y + vec.y, data->map->content))
	{
		ray->x += vec.x;
		ray->y += vec.y;
		if (ray->y > 0 && ray->x > 0)
			mlx_put_pixel(data->image, ray->x * 15, ray->y * 15, 0x00FF00FF);
		ray->len++;
	}
	return (ray);
}

void	display_player(t_data *data)
{
	t_vector	vec;
	int			d;
	float		shift;
	t_ray		*rays[WIDTH];

	vec.y = 0;
	d = 10;
	shift = 0;
	while (vec.y < d)
	{
		vec.x = 0;
		while (vec.x < d)
		{
			mlx_put_pixel(data->image, vec.x + data->player->x * 15 - 5, \
					vec.y + data->player->y * 15 - 5, 0xFF0000FF);
			vec.x++;
		}
		vec.y++;
	}
	vec.y = 0;
	while (shift < 60)
	{
		rays[(int)vec.y] = display_player_view(data->player, data, shift - 30);
		shift += 60.0 / WIDTH;
		vec.y++;
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
