/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:33:01 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/07/10 14:27:56 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	print_export(t_export *export_lst)
{
	t_export	*current;

	current = export_lst;
	while (current != NULL)
	{
		if (g_all.utils->node->out > 0)
		{
			ft_write_fd("declare -x ", g_all.utils->node->out);
			ft_write_fd(current->value, g_all.utils->node->out);
			ft_write_fd("\n", g_all.utils->node->out);
		}
		else if (!g_all.utils->node->out_fail)
		{
			printf("declare -x ");
			printf("%s\n", current->value);
		}
		current = current->next;
	}
	current = export_lst;
	g_all.utils->err = 0;
}

int	export_parsing_66(t_lexer *tmp)
{
	tmp = g_all.utils->head_lexer_lst;
	while (tmp)
	{
		if (check_parsing_export(tmp->word) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	process_word_and_add_export(t_lexer *tmp)
{
	process_word(&(g_all.utils), tmp);
	if (verif_var_exist_export(g_all.utils, tmp->word) == 0
		&& verif_equal(tmp->word, '=') == 0
		&& verif_var_exist_export_2(g_all.utils, tmp->word) == 0)
		lst_add_back_export(&(g_all.utils->export_lst), tmp->word);
	else if (check_case(tmp->word)
		&& verif_var_exist_export(g_all.utils, tmp->word) == 0)
	{
		tmp->word = case_egale(tmp->word);
		if (verif_var_exist_export(g_all.utils, tmp->word) == 0)
			lst_add_back_export(&(g_all.utils->export_lst), tmp->word);
	}
	else if (verif_var_exist_export(g_all.utils, tmp->word) == 0)
	{
		if (verif_var_exist_export(g_all.utils, tmp->word) == 0
			&& verif_equal(tmp->word, '=') == 1)
			lst_add_back_export(&(g_all.utils->export_lst), tmp->word);
		else if (verif_var_exist_export(g_all.utils, tmp->word) == 1)
			lst_add_back_export(&(g_all.utils->export_lst), tmp->word);
	}
}

void	export_remaining(t_lexer *tmp)
{
	if (export_parsing_66(tmp))
		return ;
	tmp = g_all.utils->head_lexer_lst;
	while (tmp)
	{
		if (tmp->token == ARG)
			process_word_and_add_export(tmp);
		tmp = tmp->next;
	}
}

int	export_things(t_lexer *lexer_lst)
{
	t_lexer	*tmp;

	sort_export_lst(&(g_all.utils->export_lst));
	tmp = lexer_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->word, "export") && !(tmp->next && tmp->next->word
				&& !(tmp->next->word[0] == '\0')))
			print_export(g_all.utils->export_lst);
		else if (!ft_strcmp(tmp->word, "export") && tmp->next
			&& tmp->next->token != ARG)
			print_export(g_all.utils->export_lst);
		else if ((ft_strcmp(tmp->word, "export") == 0) && (tmp->next
				&& tmp->next->token == ARG))
		{
			tmp = tmp->next;
			export_remaining(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
