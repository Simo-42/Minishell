/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:55:03 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/03/30 17:54:32 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

int	ft_strlen3(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s1, char *s2, int fd)
{
	char	*s;
	char	*final;

	if (s2)
	{
		s = ft_strjoin2(s1, s2);
		final = ft_strjoin2(s, "\n");
		write (fd, final, ft_strlen3(final));
		free (s);
		free (final);
	}
	else
	{
		write (fd, s1, ft_strlen3(s1));
		write (fd, "\n", 1);
	}
}
