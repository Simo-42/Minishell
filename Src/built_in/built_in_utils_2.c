/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:31:56 by mhajji-b          #+#    #+#             */
/*   Updated: 2023/06/12 18:33:27 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_strlen4(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin4(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2 || !s1[0] || !s2[0])
		return (NULL);
	s3 = ft_malloc(sizeof(char) * (ft_strlen4(s1) + ft_strlen4(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1 && s1[++j])
		s3[++i] = s1[j];
	j = -1;
	while (s2 && s2[++j])
		s3[++i] = s2[j];
	s3[++i] = '\0';
	return (s3);
}

size_t	ft_strlen_eguale(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (!s1 && s2 && *s2)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	str = (char *)ft_malloc(sizeof(char)
			*(ft_strlen4(s1) + ft_strlen4(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s2);
	return (str);
}
