/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/19 17:30:59 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdio.h>

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
			else if (type_chunk == 1)
				mlx_put_pixel(image, xx + (x), yy + (y), 0xFF0000FF);
			else if (type_chunk == 2)
				mlx_put_pixel(image, xx + (x * d), yy + (y * d), 0x00FF00FF);
			xx++;
		}
		yy++;
	}
}

static void	display_map(t_data *data)
{
	mlx_image_t	*image;
	int			y;
	int			x;
	t_player	*player;

	y = 0;
	image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	player = data->map->player;
	while (data->map->content[y] != NULL)
	{
		x = 0;
		while (data->map->content[y][x] != '\0')
		{
			if (data->map->content[y][x] == '1')
				puts_pixel(image, y, x, 0);
			else if (data->map->content[y][x] == player->direction)
				puts_pixel(image, player->y, player->x, 1);
			else
				puts_pixel(image, y, x, 2);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, image, 0, 0);
}

#define SPEED 4

static void	ft_hook(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->map->player->y -= SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->map->player->y += SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->map->player->x -= SPEED;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->map->player->x += SPEED;
	display_map(data);
}

void	launche(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
