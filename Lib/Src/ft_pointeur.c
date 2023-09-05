/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointeur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:38:15 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:14:55 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

static long unsigned	ft_strlenbase(char *base)
{
	long unsigned	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}	

void	ft_putbase(unsigned long nbr2, char *base)
{
	if (nbr2 >= ft_strlenbase(base))
		ft_putbase((nbr2 / ft_strlenbase(base)), base);
	ft_putchar(base[(nbr2) % ft_strlenbase(base)]);
}

int	ft_pointeur(void *ptr, char *base)
{
	unsigned long	nbr2;
	unsigned long	count;

	nbr2 = (unsigned long)ptr;
	if (!ptr)
		count = write (1, "(nil)", 5);
	else
	{
		count = ft_len_nb_hexa(nbr2);
		count = count + write (1, "0x", 2);
		ft_putbase(nbr2, base);
	}
	return (count);
}
