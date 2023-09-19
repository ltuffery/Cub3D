/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/19 16:07:53 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>

static void	puts_pixel(mlx_image_t *image, int y, int x, unsigned int color)
{
	int	xx;
	int	yy;
	int	d;

	yy = 0;
	d = 15;
	while (yy < d)
	{
		xx = 0;
		while (xx < d)
		{
			mlx_put_pixel(image, xx + (x * d), yy + (y * d), color);
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

	y = 0;
	image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	while (data->map->content[y] != NULL)
	{
		x = 0;
		while (data->map->content[y][x] != '\0')
		{
			if (data->map->content[y][x] == '1')
				puts_pixel(image, y, x, 0xFFFFFFFF);
			else if (data->map->content[y][x] == data->map->player->direction)
				puts_pixel(image, y, x, 0xFF0000FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, image, 0, 0);
}

static void	ft_hook(void *params)
{
	t_data	*data;

	data = (t_data *)params;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	launche(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	display_map(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
