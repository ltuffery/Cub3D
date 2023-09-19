/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:05:50 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/18 09:21:22 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
# include "MLX42/MLX42.h"
#include <stdbool.h>

void	close_window(void *data)
{
	mlx_close_window((mlx_t *)data);
}

void	launche(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	mlx_close_hook(data.mlx, close_window, data.mlx);
	mlx_loop(data.mlx);
}
