/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:46:17 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:15:13 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		i = write(1, "(null)", 6);
		return (i);
	}
	else
	{
		while (str[i] != '\0')
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	return (i);
}
