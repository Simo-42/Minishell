/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:57:42 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/19 03:19:17 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	sign(char c, t_quote *st)
{
	(void)st;
	if (c)
	{
		if (c == ':' || c == '=' || c == '%' || c == '^' || c == '+' || c == '~'
			|| c == '/' || c == ' '
			|| ((c == '"' || c == '\''))
			|| c == ']' || c == '@')
			return (1);
	}
	return (0);
}

static int	check(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$' || word[i] == '"' || word [i] == '\'')
			return (1);
	return (0);
}

int	need_expand_or_rm_quote(t_lexer **to_check, t_quote *state, t_expand *exp)
{
	int		i;

	exp->need_expand = 0;
	exp->quote = 0;
	i = -1;
	while ((*to_check)->word[++i])
	{
		if ((*to_check)->token == LIMITOR)
			return (0);
		if ((*to_check)->word[i] == '$')
			exp->need_expand = 1;
		if ((*to_check)->word[i] == '"' || (*to_check)->word[i] == '\'')
			exp->quote = 1;
	}
	if (exp->need_expand == 0 && exp->quote == 1)
		(*to_check)->word = remove_quote((*to_check)->word, state);
	else
		return (1);
	return (0);
}

int	dollar_at_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[--i] == '$')
		return (0);
	return (1);
}

void	expand(t_quote *state, char **env, t_lexer *tmp)
{
	t_lexer		*save;
	t_expand	*exp;

	state = ft_malloc(sizeof(t_quote));
	if (!state)
		return ;
	state_at_zero(state);
	exp = ft_malloc(sizeof(t_expand));
	if (!exp)
		return ;
	while (tmp)
	{
		save = tmp;
		if (check(tmp->word))
		{
			tmp = tmp->next;
			state_at_zero(state);
			if (!dollar_at_end(save->word))
				continue ;
			if (need_expand_or_rm_quote(&save, state, exp))
				manage_expantion(&save, state, env, exp);
		}
		else
			tmp = tmp->next;
	}
}
