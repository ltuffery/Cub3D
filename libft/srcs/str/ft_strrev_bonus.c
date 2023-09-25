/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:29:56 by chmartin          #+#    #+#             */
/*   Updated: 2023/09/25 18:14:12 by chmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_strrev(char *bgn, char *end)
{
	char	tmp;

	end--;
	while (bgn < end)
	{
		tmp = *bgn;
		*bgn = *end;
		*end = tmp;
		bgn++;
		end--;
	}
}
