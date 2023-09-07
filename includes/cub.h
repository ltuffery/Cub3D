/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:40:31 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/07 10:41:42 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define FLOOR 'F'
# define CEILING 'C'

typedef struct s_map {
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_map;

int		is_texture_line(char *line);
int		is_color_line(char *line);
void	insert_texture(t_map *map, char *line);

#endif
