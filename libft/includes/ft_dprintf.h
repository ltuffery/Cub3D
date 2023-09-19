/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <chmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:34:44 by chmartin          #+#    #+#             */
/*   Updated: 2023/02/26 10:14:24 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_opt
{
	int		width;
	int		prec;
	char	pad_char;
	char	sign_char;
	char	zero;
	char	plus;
	char	space;
	char	left;
	char	hash;
	char	dot;
}	t_opt;

int		_ft_atoi(const char **s);
int		_ft_itoa(char *buf, unsigned long nbr, int base, int lower);

void	ft_set_opt(const char **fmt, t_opt *opt);
int		ft_get_width(const char **fmt);
void	ft_set_prec(const char **fmt, t_opt *opt);
void	ft_init_opt(const char **fmt, t_opt *opt);
void	ft_set_sign(long *nbr, t_opt *opt);

int		ft_print_char(int fd, char c, t_opt *opt);
int		ft_print_str(int fd, const char *s, t_opt *opt);
int		ft_print_addr(int fd, unsigned long nbr, t_opt *opt);
int		ft_print_sgn(int fd, long nbr, t_opt *opt);
int		ft_print_usgn(int fd, unsigned long nbr, t_opt *opt, int flag);

int		ft_print_args(int fd, char c, va_list args, t_opt *opt);
int		ft_vdprintf(int fd, const char *fmt, va_list args);
int		ft_dprintf(int fd, const char *fmt, ...);
int		ft_printf(const char *fmt, ...);

#endif
