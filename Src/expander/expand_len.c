/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:56:35 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 00:44:35 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	len_squote_expantion(char *w, int *l)
{
	int		i;

	i = -1;
	while (w[i++] && w[i] != '\'')
		(*l)++;
	return (i);
}

static int	len_expantion(char *w, int *len, char *nv, t_quote *st)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (w[i++] && nv[y] && nv[y] != '=' && w[i] == nv[y])
		y++;
	if ((w[i] == '\0' || sign(w[i], st) || w[i] == '$') && nv[y]
		&& y != 0 && nv[y] == '=')
	{
		st->found = 1;
		while (nv[++y])
			(*len)++;
		return (i);
	}
	return (i);
}

int	search_in_env_len(char *w, char **nv, t_quote *st, int *len)
{
	int			x;
	int			y;
	int			i;

	st->found = 0;
	if (st->is_quote == 1 && st->is_dquote == 0)
		return (len_squote_expantion(w, len));
	else
	{
		x = -1;
		while (nv[++x])
		{
			y = 0;
			i = 1;
			if (w[i] == nv[x][y])
			{
				i = len_expantion(w, len, nv[x], st);
				if (st->found == 1)
					return (i);
			}
		}	
	}
	return (i);
}

void	type_expantion(t_lexer **expnd, t_quote *st, char **nv, t_expand *exp)
{
	int	i;

	i = -1;
	while ((*expnd)->word[++i])
	{
		quoting_state((*expnd)->word[i], st);
		if ((*expnd)->word[i] == '$')
		{
			if ((*expnd)->word[i + 1] == '\0'
				|| sign((*expnd)->word[i + 1], st))
				exp->str[exp->len++] = (*expnd)->word[i];
			else if ((*expnd)->word[i + 1] && ft_isdigit((*expnd)->word[i + 1]))
				i++;
			else if (st->is_quote == 1 && st->sq_first == 1)
				i += single_quote_expantion(&(*expnd)->word[i], exp) - 1;
			else
				i += basic_expantion(&(*expnd)->word[i], exp, nv, st) - 1;
		}
		else
			exp->str[exp->len++] = (*expnd)->word[i];
	}
}

void	len_for_expand(t_lexer **exp, t_quote *st, char **env, int *len)
{
	int	j;

	j = 0;
	while ((*exp)->word[j])
	{
		quoting_state((*exp)->word[j], st);
		if ((*exp)->word[j] == '$')
		{
			if ((*exp)->word[j + 1] && (*exp)->word[j + 1] == '?')
			{
				(*len) += ft_strlen(g_all.utils->error);
				j += 2;
			}
			else
				j += search_in_env_len(&(*exp)->word[j], env, st, len);
			if (st->found == 0 && (*exp)->word[j] && sign((*exp)->word[j], st))
				(*len)++;
		}
		else
		{
			(*len)++;
			j++;
		}
	}
}
