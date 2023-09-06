/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:06:14 by ltuffery          #+#    #+#             */
/*   Updated: 2023/09/06 11:14:08 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*my_strchr(const char *s, int c);
char	*my_strjoin(char *s1, char *s2);
char	*my_substr(char *str);
int		my_strlen(const char *s);
int		my_strlcpy(char *dest, const char *src, int size);

#endif
