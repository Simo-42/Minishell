/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:39:21 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:31:27 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_check_quotes(char *str, t_data *data)
{
	int	i;

	i = 0;
	data->squote = 0;
	data->dquote = 1;
	while (str[i])
	{
		if (str[i] == '"' && !data->squote && !data->dquote)
			data->dquote = 1;
		else if (str[i] == '"' && !data->squote && data->dquote)
			data->dquote = 0;
		else if (str[i] == '\'' && !data->squote && data->dquote)
			data->squote = 1;
		else if (str[i] == '\'' && data->squote && data->dquote)
			data->squote = 0;
		i++;
	}
	if (data->squote == data->dquote)
	{
		write(2, "minishell: syntax error quote not closed\n", 41);
		return (0);
	}
	return (1);
}

int	check_redir(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] == '\0')
		return (0);
	if ((str[i] == '>' && str[i + 1] == '>') || str[i] == '>'
		|| (str[i] == '<' && str[i + 1] == '<'))
	{
		if (str[i + 2] == '\0')
			return (0);
	}
	return (1);
}

int	base_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
	{
		write (2, "zsh: parse error near `|'\n", 27);
		return (0);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		if (!check_redir(str))
		{
			write(2, "syntax error near unexpected token\n", 35);
			return (0);
		}
	}
	return (1);
}

int	ft_cloporte(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if (tmp->token == GR || tmp->token == GR_DBE
			|| tmp->token == LESS || tmp->token == LESS_DBE)
		{
			tmp = tmp->next;
			if (tmp == NULL || tmp->word[0] == '\0')
			{
				write(2, "syntax error near unexpected token\n", 35);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	tmp = data->lexer_list;
	return (1);
}

int	ft_parser(t_data *data)
{
	if (!ft_check_quotes(data->line, data))
		return (0);
	if (!base_check(data->line))
		return (0);
	if (!pipe_parse(data))
		return (0);
	if (!ft_cloporte(data))
		return (0);
	if (!ft_arrow(data))
		return (0);
	if (!ft_tiret(data->line))
		return (0);
	if (!chevron_pipe(data->line))
		return (0);
	return (1);
}
