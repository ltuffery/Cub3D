/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/04 19:56:41 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int	colision(float x, float y, char **map)
{
	return (map[(int)y][(int)x] == '1');
}

static t_ray	*display_player_view(t_player *p, t_data *data, float shift)
{
	t_vector	vec;
	t_ray		*ray;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	vec.x = (p->x + cosf((p->direction->degree + shift) * PI / 180) \
			- p->x) / LENGTH;
	vec.y = (p->y + sinf((p->direction->degree + shift) * PI / 180) \
			- p->y) / LENGTH;
	ray->x = p->x;
	ray->y = p->y;
	while (!colision(ray->x + vec.x, ray->y, data->map->content) && \
			!colision(ray->x, ray->y + vec.y, data->map->content))
	{
		ray->x += vec.x;
		ray->y += vec.y;
	}
	ray->len = sqrtf(powf(p->x - ray->x, 2) + powf(p->y - ray->y, 2));
	if (ray->len == 0)
		ray->len = pow(10, -30);
	ray->side = colision(ray->x + vec.x, ray->y, data->map->content);
	return (ray);
}

void	display_player(t_data *data)
{
	int		i;
	float	shift;

	shift = 0;
	i = 0;
	while (shift < 60)
	{
		data->rays[i] = display_player_view(data->player, data, shift - 30);
		shift += 60.0 / WIDTH;
		i++;
	}
	data->rays[i] = NULL;
}

static void	dda(t_data *data, int x, float y1, float y2)
{
	double			longueur;
	unsigned int	color;
	mlx_texture_t	*texture;
	unsigned int	i;
	int				cor_x;

	longueur = fabsl(y2 - y1);
	i = 1;
	texture = get_texture_face(data, data->rays[x]);
	if (y1 < 0)
	{
		i -= (int)y1;
		y1 -= y1;
	}
	while (i <= longueur)
	{
		y1 += 1.0;
		if (y1 > HEIGHT)
			break ;
		cor_x = get_pixel_point(texture, data->rays[x], \
				data->player, i / longueur);
		color = get_pixel_color(texture->pixels, cor_x);
		if (y1 > 0 && x > 0 && (int)y1 < HEIGHT)
			mlx_put_pixel(data->image, x, y1, color);
		i++;
	}
}

void	display_map(t_data *data)
{
	int		i;
	float	calc;

	i = 0;
	draw_bg(data->image, data->map->floor, data->map->ceiling);
	while (i < WIDTH)
	{
		calc = 400.0 / (data->rays[i]->len);
		if (calc < 0)
			calc = 0;
		dda(data, i, HEIGHT / 2.0 - calc, HEIGHT / 2.0 + calc);
		i++;
	}
}
