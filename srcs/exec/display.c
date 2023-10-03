/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:23:13 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/03 21:12:42 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*static void	puts_pixel(mlx_image_t *image, int y, int x, int type_chunk)
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
}*/

static int	colision(float x, float y, char **map)
{
	return (map[(int)y][(int)x] == '1');
}

static t_ray	*display_player_view(t_player *player, t_data *data, float shift)
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
		// if (ray->y > 0 && ray->x > 0)
		// 	 mlx_put_pixel(data->image, ray->x * 15, ray->y * 15, 0x00FF00FF);
	}
	ray->len = sqrtf(powf((player->x - ray->x), 2) + powf((player->y - ray->y), 2));
	ray->side = colision(ray->x + vec.x, ray->y, data->map->content);
	return (ray);
}

void	display_player(t_data *data)
{
	t_vector	vec;
	int			d;
	float		shift;

	vec.y = 0;
	d = 10;
	shift = 0;
	while (vec.y < d)
	{
		vec.x = 0;
		while (vec.x < d)
		{
			//mlx_put_pixel(data->image, vec.x + data->player->x * 15 - 5, \
			//		vec.y + data->player->y * 15 - 5, 0xFF0000FF);
			vec.x++;
		}
		vec.y++;
	}
	vec.y = 0;
	while (shift < 60)
	{
		data->rays[(int)vec.y] = display_player_view(data->player, data, shift - 30);
		shift += 60.0 / WIDTH;
		vec.y++;
	}
	data->rays[(int)vec.y] = NULL;
}

static mlx_texture_t	*get_texture_face(t_data *data, t_ray *ray)
{
	if (!ray->side)
	{
		if (ray->y > data->player->y)
			return data->map->so;
		else
			return data->map->no;
	}
	else
	{
		if (ray->x < data->player->x)
			return data->map->we;
		else
			return data->map->ea;
	}
}

static void	dda(t_data *data, float x1, long double y1, float x2, long double y2, t_ray *ray)
{
    long double longueur, dx, dy, x, y;
	unsigned int	color;
	mlx_texture_t	*texture;

    if (fabsl(x2 - x1) >= fabsl(y2 - y1)) {
        longueur = fabsl(x2 - x1);
    } else {
        longueur = fabsl(y2 - y1);
    }

    dx = (x2 - x1) / longueur;
    dy = (y2 - y1) / longueur;
    x = x1;
    y = y1;
    int i = 1;
	int	cor_x;
	int	cor_y;

	texture = get_texture_face(data, ray);
    while (i <= longueur) {
        x += dx;
        y += dy;
		cor_x = (int)((ray->x - (int)ray->x) * texture->width) * 4;
		if (ray->side)
			cor_x = (int)((ray->y - (int)ray->y) * texture->width) * 4;
		if ((ray->side && ray->x < data->player->x) || (!ray->side && ray->y > data->player->y))
			cor_x = (texture->width - 1) * 4 - cor_x;
		cor_y = (float)(i) / longueur * texture->height;
		cor_x += cor_y * texture->width * 4;
		color = texture->pixels[cor_x] << 24;
		color |= texture->pixels[cor_x + 1] << 16;
		color |= texture->pixels[cor_x + 2] << 8;
		color |= texture->pixels[cor_x + 3];
		if (y > 0 && x > 0 && (int)y < HEIGHT)
		 	mlx_put_pixel(data->image, x, y, color);
        i++;
    }
}

void	display_map(t_data *data)
{
	int	i;
	int	j;
	long double		calc;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (j < HEIGHT / 2)
				mlx_put_pixel(data->image, i, j, data->map->ceiling);
			else
				mlx_put_pixel(data->image, i, j, data->map->floor);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		calc = 400.0 / (data->rays[i]->len);
		if (calc < 0)
			calc = 0;
		else if (calc > (float)HEIGHT)
			calc = HEIGHT;
		dda(data, i, HEIGHT / 2.0 - calc, \
				i, HEIGHT / 2.0 + calc, data->rays[i]);
		i++;
	}
}
