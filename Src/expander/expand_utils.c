/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:16:25 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 00:44:38 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	state_at_zero(t_quote *state)
{
	state->is_dquote = 0;
	state->is_quote = 0;
}

int	ft_len_nb(long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_is_neg(char *res, long n, int i)
{
	n = n * (-1);
	res = ft_malloc(sizeof(char) * i + 2);
	if (!res)
		return (0);
	res[0] = '-';
	res[i + 1] = '\0';
	while (i >= 1)
	{
		res[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		i;
	char	*res;

	nb = (long)n;
	res = 0;
	i = ft_len_nb(nb);
	if (nb < 0)
	{
		res = ft_is_neg(res, nb, i);
		return (res);
	}
	res = ft_malloc(sizeof(char) * i + 1);
	res[i] = '\0';
	if (!res)
		return (0);
	i--;
	while (i >= 0)
	{
		res[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (res);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
