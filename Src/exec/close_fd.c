/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:25:51 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 15:58:31 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	close_pipe(int *fd)
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
	return (1);
}

int	close_fd(void)
{
	g_all.utils->node = g_all.utils->head_node_lst;
	while (g_all.utils->node)
	{
		if (g_all.utils->node->in > 1)
			close(g_all.utils->node->in);
		if (g_all.utils->node->out > 1)
			close(g_all.utils->node->out);
		g_all.utils->node = g_all.utils->node->next;
	}
	return (1);
}
