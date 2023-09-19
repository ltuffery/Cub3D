/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <chmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:31:35 by chmartin          #+#    #+#             */
/*   Updated: 2023/09/19 17:32:39 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_dprintf.h"

int	ft_print_char(int fd, char c, t_opt *opt)
{
	int	printed;

	printed = 0;
	if (!opt->left)
		while (opt->width-- > 1)
			printed += write(fd, " ", 1);
	printed += write(fd, &c, 1);
	while (opt->width-- > 1)
		printed += write(fd, " ", 1);
	return (printed);
}

int	ft_print_str(int fd, const char *s, t_opt *opt)
{
	int	len;
	int	printed;

	printed = 0;
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (opt->dot && len > opt->prec)
		len = opt->prec;
	if (!opt->left)
		while (len < opt->width--)
			printed += write(fd, " ", 1);
	printed += write(fd, s, len);
	while (len < opt->width--)
		printed += write(fd, " ", 1);
	return (printed);
}

int	ft_print_addr(int fd, unsigned long nbr, t_opt *opt)
{
	int			printed;
	char		buf[16];
	const int	len = _ft_itoa(buf, nbr, 16, 32);

	printed = 0;
	if (nbr == 0)
	{
		printed += ft_print_str(fd, "(nil)", opt);
		return (printed);
	}
	opt->width -= 2 + len;
	if (!opt->left)
		while (opt->width-- > 0)
			printed += write(fd, " ", 1);
	printed += write(fd, "0x", 2) + write(fd, buf, len);
	while (opt->width-- > 0)
		printed += write(fd, " ", 1);
	return (printed);
}

int	ft_print_sgn(int fd, long nbr, t_opt *opt)
{
	int		i;
	int		len;
	int		printed;
	char	buf[32];

	printed = 0;
	ft_set_sign(&nbr, opt);
	len = _ft_itoa(buf, nbr, 10, 0);
	opt->width -= ft_max(len, opt->prec) * (nbr || !opt->dot || opt->prec);
	if (!opt->left && (opt->dot || !opt->zero))
		while (opt->width-- > 0)
			printed += write(fd, " ", 1);
	if (opt->sign_char)
		printed += write(fd, &opt->sign_char, 1);
	if (!opt->left)
		while (opt->width-- > 0)
			printed += write(fd, &opt->pad_char, 1);
	i = ft_max(len, opt->prec);
	while (len < i--)
		printed += write(fd, "0", 1);
	if (nbr || !opt->dot || opt->prec)
		printed += write(fd, buf, len);
	while (opt->width-- > 0)
		printed += write(fd, " ", 1);
	return (printed);
}

int	ft_print_usgn(int fd, unsigned long nbr, t_opt *opt, int flag)
{
	int			i;
	int			printed;
	char		buf[32];
	const int	len = _ft_itoa(buf, nbr, 10 + 6 * (flag > 10), 32 * (flag > 16));

	printed = 0;
	opt->width -= (nbr && opt->hash) << 1;
	opt->width -= ft_max(len, opt->prec) * (nbr || !opt->dot || opt->prec);
	if (!opt->left && (opt->dot || !opt->zero))
		while (opt->width-- > 0)
			printed += write(fd, " ", 1);
	i = 'X' | (32 * (flag > 16));
	if (nbr && opt->hash)
		printed += write(fd, "0", 1) + write(fd, &i, 1);
	if (!opt->left)
		while (opt->width-- > 0)
			printed += write(fd, &opt->pad_char, 1);
	i = ft_max(len, opt->prec);
	while (len < i--)
		printed += write(fd, "0", 1);
	if (nbr || !opt->dot || opt->prec)
		printed += write(fd, buf, len);
	while (opt->width-- > 0)
		printed += write(fd, " ", 1);
	return (printed);
}
