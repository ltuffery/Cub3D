/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <chmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:06:31 by chmartin          #+#    #+#             */
/*   Updated: 2023/09/19 17:32:57 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_dprintf.h"

int	_ft_atoi(const char **s)
{
	int	nbr;

	nbr = 0;
	while ('0' <= **s && **s <= '9')
		nbr = nbr * 10 + *((*s)++) - '0';
	return (nbr);
}

int	_ft_itoa(char *buf, unsigned long nbr, int base, int lower)
{
	static const char	digits[16] = "0123456789ABCDEF";
	char				*ptr;

	ptr = buf;
	while (1)
	{
		*ptr++ = digits[nbr % base] | lower;
		nbr /= base;
		if (nbr == 0)
			break ;
	}
	ft_strrev(buf, ptr);
	return (ptr - buf);
}
