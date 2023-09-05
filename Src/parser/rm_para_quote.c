/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_para_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:43:17 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/14 13:11:57 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*parse_quote(char *tmp)
{
	int	len;

	len = ft_strlen(tmp);
	if (tmp[0] == '\"' && tmp[1] == '\"')
		return (tmp);
	if (len >= 2 && tmp[0] == '"' && tmp[len - 1] == '"' && is_space(tmp,
			' ') == 0)
	{
		tmp = ft_substr(tmp, 1, (size_t)len - 2);
		return (tmp);
	}
	return (tmp);
}

char	*parse_quote2(char *tmp)
{
	int	len;

	len = ft_strlen(tmp);
	if (len >= 2 && tmp[0] == '\'' && tmp[len - 1] == '\'' && is_space(tmp,
			' ') == 0)
	{
		tmp = ft_substr(tmp, 1, (size_t)len - 2);
		return (tmp);
	}
	return (tmp);
}

char	*parse_para(char *tmp)
{
	int	len;

	len = ft_strlen(tmp);
	if (len >= 2 && tmp[0] == '(' && tmp[len - 1] == ')')
	{
		tmp = ft_substr(tmp, 1, (size_t)len - 2);
		return (tmp);
	}
	return (tmp);
}

void	rm_para_quote(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp)
	{
		tmp->word = parse_para(tmp->word);
		tmp->word = parse_quote(tmp->word);
		tmp = tmp->next;
	}
}

void	rm_para_quote2(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp)
	{
		tmp->word = parse_para(tmp->word);
		tmp->word = parse_quote2(tmp->word);
		tmp = tmp->next;
	}
}
