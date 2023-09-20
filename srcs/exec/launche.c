/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/20 15:38:36 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdio.h>

void    fps(void *data)
{
    t_data *const    game = data;
    char            *title;
    static int        time;

    time++;
    game->fps += game->mlx->delta_time;
    if (game->fps > 0.5)
    {
        game->fps = 1 / (game->fps / time);
		title = ft_itoa(game->fps);
        mlx_set_window_title(game->mlx, title);
        free(title);
        game->fps = 0;
        time = 0;
    }
}

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

static void	display_player(t_data *data)
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
			mlx_put_pixel(data->image, xx + data->map->player->x * 15 - 5, yy + data->map->player->y * 15 - 5, 0xFF0000FF);
			xx++;
		}
		yy++;
	}
}

static void	display_map(t_data *data)
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

#define SPEED 0.2

static void	ft_hook(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map->content[(int)(data->map->player->y - SPEED)][(int)data->map->player->x] != '1')
			data->map->player->y -= SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map->content[(int)(data->map->player->y + SPEED)][(int)data->map->player->x] != '1')
			data->map->player->y += SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map->content[(int)(data->map->player->y)][(int)(data->map->player->x - SPEED)] != '1')
			data->map->player->x -= SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map->content[(int)(data->map->player->y)][(int)(data->map->player->x + SPEED)] != '1')
			data->map->player->x += SPEED;
	}
	display_map(data);
	display_player(data);
}

void	launche(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	data.fps = 0;
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop_hook(data.mlx, &fps, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
