/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:52:12 by fd-arco           #+#    #+#             */
/*   Updated: 2023/02/22 16:14:58 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	ft_ecrireformat(char c, va_list ptr)
{
	int	res;

	res = 0;
	if (c == 'c')
		res = ft_putchar(va_arg(ptr, int));
	if (c == 's')
		res = ft_putstr(va_arg(ptr, char *));
	if (c == 'd' || c == 'i')
		res = ft_putnbr_base(va_arg(ptr, int), "0123456789");
	if (c == 'u')
		res = ft_putnbr_base_neg(va_arg(ptr, unsigned int), "0123456789");
	if (c == 'x')
		res = ft_putnbr_base_hex(va_arg(ptr, unsigned int), "0123456789abcdef");
	if (c == 'X')
		res = ft_putnbr_base_hex(va_arg(ptr, int), "0123456789ABCDEF");
	if (c == '%')
		res = ft_putchar('%');
	if (c == 'p')
		res = ft_pointeur(va_arg(ptr, void *), "0123456789abcdef");
	return (res);
}

int	ft_printf(const char *text, ...)
{
	va_list	ptr;
	int		res;

	res = 0;
	va_start(ptr, text);
	while (*text)
	{
		if (*text == '%')
		{
			text++;
			res = res + ft_ecrireformat(*text, ptr);
		}
		else
			res = res + ft_putchar(*text);
		text++;
	}
	va_end(ptr);
	return (res);
}

// int	main(void)
// {
// 	int res;
// 	char *s = NULL;
// 	ft_printf("%p, %p\n", ULONG_MAX, -ULONG_MAX);
// 	printf("%p, %p", ULONG_MAX, -ULONG_MAX);
// 	// printf("\n%d\n", res);
// 	// printf("nombres de caracteres : %d\n", res);
// }