/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:59:15 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/25 20:42:11 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	get_data_in_node(t_lexer **lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 1;
	tmp = *lexer_list;
	while (tmp)
	{
		if (tmp->word[0] == '|')
			i = 0;
		tmp->i = i;
		tmp = tmp->next;
		i++;
	}
}

void	get_token_in_node(t_lexer **lexer_list, t_lexer *tmp)
{
	t_lexer	*first;

	tmp = *lexer_list;
	while (tmp)
	{
		if (tmp->i == 1)
			first = tmp;
		if (tmp->i == 1 && tmp->word[0] != '<' && tmp->word[0] != '>')
			tmp->token = CMD;
		else if (tmp->i == 0)
			tmp->token = PIPE;
		else if (tmp->word[0] == '<' || tmp->word[0] == '>')
			tmp->token = which_redir(tmp);
		else if (tmp->prev->token == GR_DBE || tmp->prev->token == LESS
			|| tmp->prev->token == GR)
			tmp->token = FD;
		else if (tmp->prev->token == LESS_DBE)
			tmp->token = LIMITOR;
		else if ((tmp->prev->token == FD || tmp->prev->token == LIMITOR)
			&& (!tmp->next || tmp->next->word[0] == '|' || tmp->next))
			truc(tmp, first);
		else
			tmp->token = ARG;
		tmp = tmp->next;
	}
}

int	get_word_in_list(char *str, int i, t_lexer **lexer_list, t_lexer *tmp)
{
	char	*word;
	int		j;
	int		k;
	int		x;
	t_quote	*state;

	state = ft_malloc(sizeof(t_quote));
	if (!state)
		return (0);
	word = NULL;
	x = i;
	k = 0;
	j = 0;
	state_at_zero(state);
	ft_lexer4(str, &i, &j, state);
	word = ft_malloc(sizeof(char) * (j + 1));
	if (!word)
		return (0);
	word[j] = '\0';
	while (k < j)
		word[k++] = str[x++];
	ft_add_back_lexer(lexer_list, word);
	get_data_in_node(lexer_list);
	get_token_in_node(lexer_list, tmp);
	return (j);
}

void	ft_lexer2(t_data *data, t_lexer *tmp, t_lexer *current, int i)
{
	int	j;
	int	x;

	x = 0;
	while (data->line[i])
	{
		j = 0;
		while (data->line[i] == ' ' || \
		(data->line[i] >= 9 && data->line[i] <= 14))
			i++;
		if (!data->line || !data->line[i])
		{
			data->lexer_list = current;
			get_token_in_node(&current, tmp);
			return ;
		}
		j = get_word_in_list(data->line, i, &data->lexer_list,
				tmp);
		if (x == 0)
			current = data->lexer_list;
		i = i + j;
		x++;
	}
	data->lexer_list = current;
}

void	ft_lexer(t_data *data)
{
	int		i;
	t_lexer	*current;
	t_lexer	*tmp;

	tmp = NULL;
	current = NULL;
	data->lexer_list = NULL;
	data->nb_mots = ft_nombre_mots(data->line);
	i = 0;
	ft_lexer2(data, tmp, current, i);
}
