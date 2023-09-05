/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:30:51 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/08 17:25:12 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	sort_export_lst(t_export **head_export)
{
	int			swapped;
	t_export	*current;
	char		*temp;

	if (!head_export || !(*head_export) || !((*head_export)->next))
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head_export;
		while (!current->next)
		{
			if (ft_strcmp(current->value, current->next->value) > 0)
			{
				temp = current->value;
				current->value = current->next->value;
				current->next->value = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

t_export	*ft_new_export_node(t_export *new)
{
	new = NULL;
	new = (t_export *)ft_malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->value = ft_strdup(g_all.utils->env_lst->content);
	new->next = NULL;
	return (new);
}

t_export	*get_export_list(t_export *export_lst)
{
	t_export	*new;
	t_export	*current_new;

	current_new = NULL;
	while (g_all.utils->env_lst)
	{
		new = ft_new_export_node(new);
		if (!export_lst)
		{
			export_lst = new;
			current_new = export_lst;
		}
		else
		{
			current_new->next = new;
			current_new = current_new->next;
		}
		g_all.utils->env_lst = g_all.utils->env_lst->next;
	}
	sort_export_lst(&export_lst);
	g_all.utils->env_lst = g_all.utils->head_env_lst;
	return (export_lst);
}
