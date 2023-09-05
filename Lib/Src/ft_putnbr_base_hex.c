/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:57:31 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:15:05 by fd-arco          ###   ########.fr       */
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

int	ft_putnbr_base_hex(unsigned int nbr, char *base)
{
	long	nbr2;
	int		count;

	nbr2 = nbr;
	count = ft_len_nb_hexa(nbr2);
	if (nbr2 < 0)
	{
		ft_putchar('-');
		nbr2 = nbr2 * (-1);
		count++;
	}
	if (nbr2 >= ft_strlenbase(base))
		ft_putnbr_base((nbr2 / ft_strlenbase(base)), base);
	ft_putchar(base[(nbr2) % ft_strlenbase(base)]);
	return (count);
}
