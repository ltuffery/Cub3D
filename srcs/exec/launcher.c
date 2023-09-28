/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/28 18:52:19 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdio.h>

void	fps(void *data)
{
	t_data		*game;
	char		*title;
	static int	time;

	game = data;
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

static int	has_key_down(t_data *data)
{
	return (mlx_is_key_down(data->mlx, MLX_KEY_W) || \
			mlx_is_key_down(data->mlx, MLX_KEY_S) || \
			mlx_is_key_down(data->mlx, MLX_KEY_A) || \
			mlx_is_key_down(data->mlx, MLX_KEY_D) || \
			mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || \
			mlx_is_key_down(data->mlx, MLX_KEY_LEFT));
}

static void	ft_hook(void *data)
{
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_data *)data)->mlx);
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_W))
		move_forward(data);
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_S))
		move_back(data);
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_D))
		move_rigth(data);
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_RIGHT))
		((t_data *)data)->player->direction->degree += 1.4;
	if (mlx_is_key_down(((t_data *)data)->mlx, MLX_KEY_LEFT))
		((t_data *)data)->player->direction->degree -= 1.4;
	if (has_key_down(data))
	{
		display_map(data);
		display_player(data);
	}
}

void	launcher(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	data.fps = 0;
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.player = data.map->player;
	display_map(&data);
	display_player(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop_hook(data.mlx, &fps, &data);
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
