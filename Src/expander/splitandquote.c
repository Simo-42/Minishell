/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitandquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:52:44 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/14 12:53:46 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	len_d_array(char *word, t_quote *state)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	state->is_dquote = 0;
	state->is_quote = 0;
	while (word[++i])
	{
		quoting_state(word[i], state);
		if (on_word(word, i, state))
			j++;
	}
	return (j);
}

char	**split_word(char *word, t_quote *state)
{
	int		i;
	int		j;
	char	**arr;

	arr = ft_malloc(sizeof(char *) * (len_d_array(word, state) + 1));
	if (!arr)
		return (NULL);
	i = -1;
	j = 0;
	state->is_dquote = 0;
	state->is_quote = 0;
	while (word[++i])
	{
		quoting_state(word[i], state);
		if (on_word(word, i, state))
			arr[j++] = malloc_word(&word[i], state);
	}
	arr[j] = NULL;
	return (arr);
}

int	next_squote(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\'' && cmd[i + 1] == '\'')
		return (i);
	else if (cmd[i] == '\'')
		i++;
	while (cmd[i] && cmd[i + 1] != '\'')
		i++;
	return (i);
}

int	next_dquote(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '"' && cmd[i + 1] == '"')
		return (i);
	else if (cmd[i] == '"')
		i++;
	while (cmd[i] && cmd[i + 1] != '"')
		i++;
	return (i);
}

int	next_squote_len(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '\'')
		i++;
	while (cmd[i] && cmd[i] != '\'')
		i++;
	if (cmd[i] == '\0')
		return (i);
	quoting_state(cmd[i], state);
	i++;
	if (cmd[i] && !sep_word(cmd[i]))
	{
		while (cmd[i] && !end_word(cmd, i, state))
		{
			quoting_state(cmd[i], state);
			i++;
		}
	}
	return (i);
}
