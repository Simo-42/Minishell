/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_neg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:01:37 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:15:08 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

static int	ft_strlenbase(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}	

int	ft_putnbr_base_neg(unsigned int nbr, char *base)
{
	long long	nbr2;
	int			count;

	nbr2 = nbr;
	count = ft_len_nb(nbr2);
	if (nbr2 < 0)
		nbr2 = nbr2 * (-1);
	if (nbr2 >= ft_strlenbase(base))
		ft_putnbr_base_neg((nbr2 / ft_strlenbase(base)), base);
	ft_putchar(base[(nbr2) % ft_strlenbase(base)]);
	return (count);
}
