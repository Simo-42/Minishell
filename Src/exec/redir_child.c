/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:54:11 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 14:41:48 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	handle_in(t_exec utils, int count)
{
	if (utils.node->in >= 0)
	{
		dup2(utils.node->in, STDIN_FILENO);
		if (utils.node->in > 0)
			close(utils.node->in);
		if (utils.previous_fd)
			close(utils.previous_fd);
	}
	else if (count)
	{
		dup2(utils.previous_fd, STDIN_FILENO);
		if (utils.previous_fd > 0)
			close(utils.previous_fd);
	}
}

void	handle_out(t_exec utils, int *fd, int count)
{
	if (utils.node->out > 0)
	{
		dup2(utils.node->out, STDOUT_FILENO);
		if (utils.node->in > 0)
			close (utils.node->in);
	}
	else if (count != utils.nb_cmd - 1 && fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		close (fd[0]);
}
