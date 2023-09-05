/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoteandnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:55:26 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 20:20:59 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*malloc_for_expand(t_lexer **exp, t_quote *st, char **env)
{
	int		len;
	char	*str;

	len = 0;
	st->found = 0;
	if ((*exp)->word[0] && (*exp)->word[0] == '$' && !(*exp)->word[1])
		len++;
	len_for_expand(exp, st, env, &len);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

void	manage_expantion(t_lexer **expnd, t_quote *st, char **nv, t_expand *exp)
{	
	char	**expanded;

	exp->len = 0;
	g_all.utils->error = ft_itoa(g_all.utils->err);
	exp->str = malloc_for_expand(expnd, st, nv);
	if (!exp->str)
		return ;
	st->is_quote = 0;
	st->is_dquote = 0;
	type_expantion(expnd, st, nv, exp);
	exp->str[exp->len] = '\0';
	if (exp->need_expand == 1 && exp->quote == 0)
		expanded = split_word(exp->str, st);
	else
	{
		(*expnd)->word = remove_quote(exp->str, st);
		return ;
	}
	replace_old_node(expnd, expanded);
}

void	add_back_new_node(char **insert, t_lexer *back, t_lexer *next, int len)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	while (++i < len)
	{
		tmp = ft_malloc(sizeof(t_lexer) * (1));
		if (!tmp)
			return ;
		if (back)
			back->next = tmp;
		if (next)
			next->prev = tmp;
		tmp->prev = back;
		tmp->next = next;
		tmp->token = ARG;
		tmp->word = ft_strdup(insert[i]);
		back = tmp;
	}
}

void	replace_old_node(t_lexer **old_node, char **to_insert)
{
	int		len;
	t_lexer	*back;
	t_lexer	*next;

	len = len_darr(to_insert);
	back = (*old_node)->prev;
	next = (*old_node)->next;
	(*old_node)->word = ft_strdup(to_insert[0]);
	if (len > 1)
	{
		back = (*old_node);
		add_back_new_node(to_insert, back, next, len);
	}
}

char	*put_word_without_quote(char *old, char *nw, t_quote *state)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	state->is_quote = 0;
	state->is_dquote = 0;
	while (old[++i])
	{
		if (old[i] == '"' && state->is_quote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		if (old[i] == '\'' && state->is_dquote == 0)
		{
			quoting_state(old[i], state);
			continue ;
		}
		nw[j++] = old[i];
	}
	nw[j] = '\0';
	return (nw);
}
