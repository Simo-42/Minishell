/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:00:00 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/16 15:26:46 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_lexer	*ft_lexer_new(char *str)
{
	t_lexer	*new;

	new = ft_malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	check_redir_error(t_lexer *tmp)
{
	int	i;

	i = -1;
	if (tmp->word[0] == '>')
		while (tmp->word[++i])
			if (tmp->word[i] != '>')
				return (-1);
	if (i > 2)
		return (-1);
	if (tmp->word[0] == '<')
		while (tmp->word[++i])
			if (tmp->word[i] != '<')
				return (-1);
	if (i > 2)
		return (-1);
	return (0);
}

t_token	which_redir(t_lexer *tmp)
{
	if (!check_redir_error(tmp))
	{
		if (tmp->word[0] == '>' && tmp->word[1] == '\0')
			return (GR);
		else if (tmp->word[0] == '<' && tmp->word[1] == '\0')
			return (LESS);
		else if (tmp->word[0] == '>' && tmp->word[1] == '>')
			return (GR_DBE);
		else if (tmp->word[0] == '<' && tmp->word[1] == '<')
			return (LESS_DBE);
	}
	return (-1);
}

void	truc(t_lexer *tmp, t_lexer *first)
{	
	if (first->token != CMD)
		tmp->token = CMD;
	else
		tmp->token = ARG;
}

int	ft_nombre_mots(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (is_white_space(str[i]) && str[i])
			i++;
		if (str[i])
			count++;
		while (!is_white_space(str[i]) && str[i])
			i++;
	}
	return (count);
}
