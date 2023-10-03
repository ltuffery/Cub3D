/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/03 21:50:41 by ltuffery         ###   ########.fr       */
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
	ray->len = 0;
	while (!colision(ray->x + vec.x, ray->y, data->map->content) && \
			!colision(ray->x, ray->y + vec.y, data->map->content))
	{
		ray->x += vec.x;
		ray->y += vec.y;
	}
	ray->len = sqrtf(powf((p->x - ray->x), 2) + powf((p->y - ray->y), 2));
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

static mlx_texture_t	*get_texture_face(t_data *data, t_ray *ray)
{
	if (!ray->side)
	{
		if (ray->y > data->player->y)
			return (data->map->so);
		else
			return (data->map->no);
	}
	else
	{
		if (ray->x < data->player->x)
			return (data->map->we);
		else
			return (data->map->ea);
	}
}

static int	get_pixel_point(mlx_texture_t *texture, t_ray *ray, \
		t_player *player, float y)
{
	int	cor_x;

	cor_x = (ray->x - (int)ray->x) * texture->width;
	cor_x *= 4;
	if (ray->side)
	{
		cor_x = (ray->y - (int)ray->y) * texture->width;
		cor_x *= 4;
	}
	if ((ray->side && ray->x < player->x) || (!ray->side && ray->y > player->y))
		cor_x = (texture->width - 1) * 4 - cor_x;
	cor_x += (int)(y * texture->height) * texture->width * 4;
	return (cor_x);
}

static unsigned int	get_pixel_color(uint8_t *pixels, int point)
{
	unsigned int	color;

	color = pixels[point] << 24;
	color |= pixels[point + 1] << 16;
	color |= pixels[point + 2] << 8;
	color |= pixels[point + 3];
	return (color);
}

static void	dda(t_data *data, float x, float y1, float y2, t_ray *ray)
{
	double			longueur;
	unsigned int	color;
	mlx_texture_t	*texture;
	int				i;
	int				cor_x;

	longueur = fabsl(y2 - y1);
	i = 1;
	texture = get_texture_face(data, ray);
	while (i <= longueur)
	{
		y1 += 1.0;
		cor_x = get_pixel_point(texture, ray, data->player, i / longueur);
		color = get_pixel_color(texture->pixels, cor_x);
		if (y1 > 0 && x > 0 && (int)y1 < HEIGHT)
			mlx_put_pixel(data->image, x, y1, color);
		i++;
	}
}

static void	draw_bg(mlx_image_t *image, unsigned int flr, unsigned int clg)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(image, i, j, clg);
			else
				mlx_put_pixel(image, i, j, flr);
			j++;
		}
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
		else if (calc > (float)HEIGHT)
			calc = HEIGHT;
		dda(data, i, HEIGHT / 2.0 - calc, \
				HEIGHT / 2.0 + calc, data->rays[i]);
		i++;
	}
}
