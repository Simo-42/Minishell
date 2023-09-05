/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:33:03 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/08 16:09:33 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../../Include/minishell.h"

int	strlen2(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	s3 = ft_malloc(sizeof(char) * (strlen2(s1) + strlen2(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[++j])
		s3[++i] = s1[j];
	j = -1;
	while (s2[++j])
		s3[++i] = s2[j];
	s3[++i] = '\0';
	return (s3);
}

// int	main(void)
// {
// 	char *str;
// 	char *str1;
// 	char *str2;

// 	str2 = "";
// 	str1 = "bonjour";
// 	str = ft_strjoin2(str1, str2);
// 	printf("str = %s\n", str);
// 	free(str);
// }