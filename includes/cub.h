/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:40:31 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/20 15:12:47 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stddef.h>
# include "MLX42/MLX42.h"

# define FLOOR 'F'
# define CEILING 'C'
# define WIDTH 1080
# define HEIGHT 720
# define TITLE "CUB3D"

typedef struct s_player {
	float	x;
	float	y;
	char	direction; // mettre en float
}	t_player;

typedef struct s_map {
	int					fd;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	unsigned int		floor;
	unsigned int		ceiling;
	t_player			*player;
	char				**content;
}	t_map;

typedef struct s_data {
	t_map	*map;
	mlx_t	*mlx;
	float	fps;
	mlx_image_t	*image;
}	t_data;

int		is_texture_line(char *line);
void	insert_texture(t_map **map, char *line);
int		is_color_line(char *line);
void	insert_color(t_map **map, char *line);
int		is_map_line(char *line);
void	insert_map(t_map **map, char *line);
void	set_player(t_map **map);
int		is_valid_map(char **content);
void	setup_config(t_map *map);

char	*fill_str(char *str, char fill, size_t max);
size_t	find_max_len(char **content);

void	launche(t_map *map);

#endif
