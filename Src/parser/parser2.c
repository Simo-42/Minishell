/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:52:29 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/25 18:54:09 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	pipe_parse2(t_data *data)
{
	int		k;
	t_lexer	*tmp;

	k = 0;
	tmp = data->lexer_list;
	while (tmp)
	{
		k = 0;
		if ((tmp->word[k] == '>' && tmp->word[k + 1] == '|')
			|| (tmp->word[k] == '<' && tmp->word[k + 1] == '|'))
		{
			write (2, "zsh: parse error near `|'\n", 26);
			k++;
			return (0);
		}
		if (tmp->word[k] == '|' && tmp->word[k + 1] == '<')
		{
			write (2, "zsh: no such file or directory\n", 32);
			k++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_chevron(char *str, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			k++;
		}
		i++;
	}
	if (k > 2)
		return (0);
	return (1);
}

int	pipe_parse(t_data *data)
{
	int		k;
	t_lexer	*tmp;

	k = 0;
	tmp = NULL;
	tmp = data->lexer_list;
	while (tmp)
	{
		k = 0;
		if (!ft_chevron(tmp->word, '<') || (!ft_chevron(tmp->word, '>')))
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (0);
		}
		if (tmp->word[k] == '|' && tmp->word[k + 1] == '|')
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (0);
		}
		if (!pipe_parse2(data))
			return (0);
		tmp = tmp->next;
	}
	tmp = data->lexer_list;
	return (1);
}

int	ft_arrow2(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if ((tmp->token == GR_DBE || tmp->token == GR))
		{
			if (tmp->next->token == LESS_DBE || tmp->next->token == LESS
				|| tmp->next->token == GR_DBE || tmp->next->token == GR
				|| tmp->next->token == PIPE)
				return (0);
		}
		if (tmp->token == LESS_DBE || tmp->token == LESS)
		{
			if (tmp->next->token == LESS_DBE || tmp->next->token == LESS
				|| tmp->next->token == GR_DBE || tmp->next->token == GR
				|| tmp->next->token == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_arrow(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
		{
			tmp = tmp->next;
			if (tmp == NULL || tmp->token == PIPE || tmp->word[0] == '\0')
			{
				write(2, "syntax error near unexpected token\n", 35);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	if (!ft_arrow2(data))
	{
		write(2, "syntax error near unexpected token\n", 35);
		return (0);
	}
	tmp = data->lexer_list;
	return (1);
}
