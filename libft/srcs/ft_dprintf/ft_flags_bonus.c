/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <chmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:17:01 by chmartin          #+#    #+#             */
/*   Updated: 2023/09/19 17:32:17 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_dprintf.h"

void	ft_set_opt(const char **fmt, t_opt *opt)
{
	while (1)
	{
		(*fmt)++;
		if (**fmt == '-')
			opt->left = 1;
		else if (**fmt == '+')
			opt->plus = 1;
		else if (**fmt == ' ')
			opt->space = 1;
		else if (**fmt == '#')
			opt->hash = 1;
		else if (**fmt == '0')
		{
			opt->zero = 1;
			opt->pad_char = '0';
		}
		else
			return ;
	}
}

int	ft_get_width(const char **fmt)
{
	int	width;

	width = 0;
	if ('0' <= **fmt && **fmt <= '9')
		width = _ft_atoi(fmt);
	return (width);
}

void	ft_set_prec(const char **fmt, t_opt *opt)
{
	opt->prec = 0;
	opt->dot = 0;
	if (**fmt == '.')
	{
		(*fmt)++;
		opt->dot = 1;
		if ('0' <= **fmt && **fmt <= '9')
			opt->prec = _ft_atoi(fmt);
	}
}

void	ft_init_opt(const char **fmt, t_opt *opt)
{
	opt->zero = 0;
	opt->pad_char = ' ';
	opt->plus = 0;
	opt->space = 0;
	opt->left = 0;
	opt->hash = 0;
	ft_set_opt(fmt, opt);
	opt->width = ft_get_width(fmt);
	ft_set_prec(fmt, opt);
}

void	ft_set_sign(long *nbr, t_opt *opt)
{
	opt->sign_char = 0;
	if (*nbr < 0)
	{
		opt->sign_char = '-';
		*nbr *= -1;
		opt->width--;
	}
	else if (opt->plus)
	{
		opt->sign_char = '+';
		opt->width--;
	}
	else if (opt->space)
	{
		opt->sign_char = ' ';
		opt->width--;
	}
}
