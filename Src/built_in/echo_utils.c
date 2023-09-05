/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:06:06 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/10 18:15:09 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	freetab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return ;
}

int	ft_word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	*ft_put_word_in_malloc(char *s, char c, char *tab)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c))
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_malloc_word(char **tab, char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			tab[k] = ft_malloc(sizeof(char) * (j + 1));
			if (!tab[k])
				freetab(tab, k - 1);
			tab[k] = ft_put_word_in_malloc(&s[i], c, tab[k]);
			i = i + j;
			k++;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		word_count;

	if (!s)
		return (0);
	word_count = ft_word_count((char *)s, c);
	tab = ft_malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	tab[word_count] = NULL;
	ft_malloc_word(tab, (char *)s, c);
	return (tab);
}
