/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <chmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:17:38 by chmartin          #+#    #+#             */
/*   Updated: 2023/09/19 17:31:36 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_dprintf.h"

int	ft_print_args(int fd, char c, va_list args, t_opt *opt)
{
	int	printed;

	printed = 0;
	if (c == 'c')
		printed += ft_print_char(fd, va_arg(args, int), opt);
	else if (c == 's')
		printed += ft_print_str(fd, va_arg(args, char *), opt);
	else if (c == 'p')
		printed += ft_print_addr(fd, (unsigned long)va_arg(args, void *),
				opt);
	else if (c == 'd' || c == 'i')
		printed += ft_print_sgn(fd, va_arg(args, int), opt);
	else if (c == 'u')
		printed += ft_print_usgn(fd, va_arg(args, unsigned), opt, 10 + 0);
	else if (c == 'x')
		printed += ft_print_usgn(fd, va_arg(args, unsigned), opt, 16 + 32);
	else if (c == 'X')
		printed += ft_print_usgn(fd, va_arg(args, unsigned), opt, 16 + 0);
	else if (c == '%')
		printed += ft_print_char(fd, '%', opt);
	return (printed);
}

int	ft_vdprintf(int fd, const char *fmt, va_list args)
{
	t_opt	opt;
	int		printed;
	int		len;

	printed = 0;
	len = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			len++;
			fmt++;
			continue ;
		}
		printed += write(fd, fmt - len, len);
		len = 0;
		ft_init_opt(&fmt, &opt);
		printed += ft_print_args(fd, *fmt, args, &opt);
		fmt++;
	}
	printed += write(fd, fmt - len, len);
	return (printed);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	args;
	int		printed;

	if (fmt == NULL)
		return (-1);
	va_start(args, fmt);
	printed = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return (printed);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		printed;

	if (fmt == NULL)
		return (-1);
	va_start(args, fmt);
	printed = ft_vdprintf(1, fmt, args);
	va_end(args);
	return (printed);
}
