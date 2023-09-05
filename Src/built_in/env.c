/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:45:45 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 17:42:53 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*unset_var(t_lexer *lexer_lst)
{
	t_lexer	*tmp;

	tmp = lexer_lst;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->word, "unset", 5))
		{
			if (tmp->next && tmp->next->word && !(tmp->next->word[0] == '\0'))
			{
				tmp = tmp->next;
				return (tmp->word);
			}
			else
			{
				write(2, "unset: not enough arguments\n", 28);
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	env_display(t_lexer *lexer_lst)
{
	t_lexer	*tmp;

	tmp = lexer_lst;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->word, "env"))
		{
			display_env();
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	display_env(void)
{
	t_env	*current;

	current = g_all.utils->env_lst;
	if (g_all.utils->node->out > 0)
	{
		while (current)
		{
			if (ft_write_fd(current->content, g_all.utils->node->out))
				return ;
			ft_write_fd("\n", g_all.utils->node->out);
			current = current->next;
		}
	}
	else if (!g_all.utils->node->out_fail)
	{
		while (current)
		{
			printf("%s\n", current->content);
			current = current->next;
		}
	}
}

void	remove_export_node(t_export *current, t_export *prev)
{
	if (prev == NULL)
		g_all.utils->export_lst = current->next;
	else
		prev->next = current->next;
}

int	unset_things(t_lexer *lexer_lst)
{
	if (env_display(lexer_lst) == 0)
	{
		g_all.utils->var = NULL;
		g_all.utils->var = unset_var(lexer_lst);
		if (g_all.utils->var)
		{
			remove_node(g_all.utils->var);
			remove_node_export(g_all.utils->var);
		}
	}
	g_all.utils->err = 0;
	return (0);
}
