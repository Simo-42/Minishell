/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:49:02 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 17:41:02 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_write_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (write (fd, str, i) == -1)
	{
		ft_printf("write error: no space left on device\n");
		g_all.utils->err = 1;
		return (1);
	}
	return (0);
}

void	ft_add_back_lexer(t_lexer **lexer_list, char *str)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_lexer_new(str);
	if (*lexer_list == NULL)
	{
		*lexer_list = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		current = *lexer_list;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
	return ;
}

void	ft_lexer4(char *str, int *i, int *j, t_quote *state)
{
	while (str[*i])
	{
		quoting_state(str[*i], state);
		if (!is_white_space(str[*i])
			&& (!state->is_dquote && !state->is_quote))
		{
			(*j)++;
			(*i)++;
		}
		else if (is_white_space(str[*i])
			&& (!state->is_dquote && !state->is_quote))
			break ;
		else if (state->is_dquote || state->is_quote)
		{
			(*j)++;
			(*i)++;
		}
	}
}
