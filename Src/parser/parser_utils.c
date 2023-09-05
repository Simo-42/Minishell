/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:52:19 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/18 20:57:48 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

size_t	ft_strlen3(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*nouveau;

	if (s && start >= ft_strlen3(s))
	{
		nouveau = ft_malloc(sizeof(char));
		if (!nouveau)
			return (NULL);
		nouveau[0] = '\0';
		return (nouveau);
	}
	nouveau = ft_malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!nouveau || !s)
		return (NULL);
	nouveau[len] = '\0';
	while (i < len && s[i + start])
	{
		nouveau[i] = s[i + start];
		i++;
	}
	nouveau[i] = '\0';
	return (nouveau);
}

int	is_white_space(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	is_space(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			ft_printf("found space");
			return (1);
		}
		i++;
	}
	return (0);
}
