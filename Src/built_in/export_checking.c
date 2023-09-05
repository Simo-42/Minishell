/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:35:57 by mhajji-b          #+#    #+#             */
/*   Updated: 2023/06/20 20:17:59 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	export_quotes(t_export *data)
{
	t_export	*tmp;

	tmp = data;
	while (tmp)
	{
		if (check_case(tmp->value) && check_case_2(tmp->value))
			tmp->value = case_egale(tmp->value);
		tmp = tmp->next;
	}
	tmp = data;
}

int	check_case_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_case(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	process_word(t_exec **utils, t_lexer *tmp)
{
	remove_double_quotes(tmp->word);
	remove_single_quotes(tmp->word);
	if (verif_equal(tmp->word, '=') && verif_var_exist(*utils, tmp->word) == 0)
	{
		lst_add_back(*utils, tmp->word);
	}
}
