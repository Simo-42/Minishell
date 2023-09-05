/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:35:09 by mhajji-b          #+#    #+#             */
/*   Updated: 2023/06/12 18:35:23 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_export	*create_node_str_export(char *str)
{
	t_export	*node;

	node = ft_malloc(sizeof(t_export));
	if (node)
	{
		node->value = str;
		node->next = NULL;
	}
	return (node);
}

void	lst_add_back_export(t_export **head, char *str)
{
	t_export	*current;

	if (*head == NULL)
	{
		*head = create_node_str_export(str);
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = create_node_str_export(str);
	}
}
