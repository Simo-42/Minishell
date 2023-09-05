/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:36:54 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:23:34 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_node	*ft_add_back_node(t_node *node_lst, t_node *new)
{
	t_node	*tmp;

	tmp = node_lst;
	if (!tmp)
		return (new);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (node_lst);
}

void	get_all_node(t_node *node, t_lexer *lexer_lst, t_exec *utils)
{
	int	i;

	i = -1;
	while (++i < utils->nb_node)
	{
		node = ft_malloc(sizeof(t_node));
		if (!node)
			return ;
		node->index = i;
		get_in(node, lexer_lst);
		get_out(node, lexer_lst);
		node->next = NULL;
		node->has_cmd = has_cmd(lexer_lst);
		utils->node = ft_add_back_node(utils->node, node);
		while (lexer_lst && lexer_lst->token != PIPE)
			lexer_lst = lexer_lst->next;
		if (lexer_lst)
			lexer_lst = lexer_lst->next;
	}
		lexer_lst = utils->head_lexer_lst;
}

void	ft_init_exec(t_data *data)
{
	t_node	*node;

	g_all.utils->node = NULL;
	g_all.utils->is_here_doc = 1;
	g_all.utils->can_run = 1;
	g_all.utils->hd = NULL;
	g_all.utils->nb_cmd = nb_cmd(data->lexer_list);
	g_all.utils->nb_node = nb_node(data->lexer_list);
	g_all.utils->head_lexer_lst = data->lexer_list;
	g_all.utils->env = data->env;
	if (!(g_all.utils->export_lst))
	{
		g_all.utils->export_lst = get_export_list(g_all.utils->export_lst);
		export_quotes(g_all.utils->export_lst);
	}
	node = NULL;
	get_all_node(node, data->lexer_list, g_all.utils);
	g_all.utils->is_here_doc = 0;
	handle_sig();
	g_all.utils->head_node_lst = g_all.utils->node;
}
