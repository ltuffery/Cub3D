/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:13:33 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/05 20:34:39 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

mlx_texture_t	*get_texture_face(t_data *data, t_ray *ray)
{
	if (!ray->side)
	{
		if (sinf((ray->angle + data->player->direction->degree) * PI / 180) > 0)
			return (data->map->so);
		else
			return (data->map->no);
	}
	else
	{
		if (cosf((ray->angle + data->player->direction->degree) * PI / 180) < 0)
			return (data->map->we);
		else
			return (data->map->ea);
	}
}

int	get_pixel_point(mlx_texture_t *texture, t_ray *ray, \
		t_player *player, float y)
{
	int	cor_x;

	cor_x = (ray->x - (int)ray->x) * texture->width;
	if (ray->side)
		cor_x = (ray->y - (int)ray->y) * texture->width;
	if ((ray->side && ray->x < player->x) || (!ray->side && ray->y > player->y))
		cor_x = (texture->width - 1) - cor_x;
	cor_x += (int)(y * texture->height) * texture->width;
	cor_x *= 4;
	return (cor_x);
}

unsigned int	get_pixel_color(mlx_texture_t *texture, unsigned int point)
{
	unsigned int	color;

	if (point >= texture->height * texture->width * 4)
		return (0);
	color = texture->pixels[point] << 24;
	color |= texture->pixels[point + 1] << 16;
	color |= texture->pixels[point + 2] << 8;
	color |= texture->pixels[point + 3];
	return (color);
}

void	draw_bg(mlx_image_t *image, unsigned int flr, unsigned int clg)
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
