/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:50:02 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 15:41:45 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*malloc_word_without_quote(int len, char *old, t_quote *state)
{
	char	*nw;

	nw = ft_malloc(sizeof(char) * (len + 1));
	if (!nw)
		return (NULL);
	return (put_word_without_quote(old, nw, state));
}

char	*remove_quote(char *old, t_quote *state)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	state->is_quote = 0;
	state->is_dquote = 0;
	while (old[++i])
	{
		quoting_state(old[i], state);
		if (state->is_dquote == 1 && state->is_quote == 1)
			len++;
		if (old[i] == '"' && state->is_quote == 0)
			continue ;
		if (old[i] == '\'' && state->is_dquote == 0)
			continue ;
		len++;
	}
	return (malloc_word_without_quote(len, old, state));
}

int	on_word(char *word, int index, t_quote *state)
{
	if (word[index] != ' ' && (index == 0 || word[index - 1] == ' '))
	{
		if ((word[index] == '"' && state->is_dquote == 0)
			|| (word[index] == '\'' && state->is_dquote == 0))
		{
			if (word[index + 1])
				if (word[index + 1] != ' ')
					return (1);
		}
		else
			return (1);
	}
	return (0);
}

char	*copy_word(char *word, t_quote *state, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (word[i] && word[i] != ' ')
	{
		if ((word[i] == '"' && state->is_quote == 0)
			|| (word[i] == '\'' && state->is_dquote == 0))
			i++;
		else
		{
			str[j++] = word[i];
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*malloc_word(char *word, t_quote *state)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (word[i] && word[i] != ' ')
	{
		if ((word[i] == '"' && state->is_quote == 0)
			|| (word[i] == '\'' && state->is_dquote == 0))
			i++;
		else
		{
			i++;
			j++;
		}
	}
	str = ft_malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	return (copy_word(word, state, str));
}
