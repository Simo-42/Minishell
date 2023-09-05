/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_nb_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:56:13 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:14:51 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_len_nb_hexa(unsigned long n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	while (n != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}
