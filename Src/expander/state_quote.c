/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:50:48 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/14 12:58:56 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	next_dquote_len(char *cmd, int i, t_quote *state)
{
	if (cmd[i] == '"')
		i++;
	while (cmd[i] && cmd[i] != '"')
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

void	quoting_state(char c, t_quote *state)
{
	if (c == '\'')
	{
		if (state->is_quote == 0)
			state->is_quote = 1;
		else
		{
			state->sq_first = 0;
			state->is_quote = 0;
		}
	}
	else if (c == '"')
	{
		if (state->is_dquote == 0)
			state->is_dquote = 1;
		else
			state->is_dquote = 0;
	}
	if (state->is_quote == 1 && state->is_dquote == 0)
		state->sq_first = 1;
}

int	sep_word(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}

int	end_word(char *cmd, int i, t_quote *state)
{
	if (sep_word(cmd[i]) && state->is_dquote == 0 && state->is_quote == 0)
		return (1);
	return (0);
}

int	len_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
