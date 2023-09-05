/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:48:16 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 00:03:35 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_lexer	*go_next_cmd(t_lexer *lexer_list)
{
	while (lexer_list && lexer_list->token != PIPE)
		lexer_list = lexer_list->next;
	if (lexer_list && lexer_list->token == PIPE)
		lexer_list = lexer_list->next;
	return (lexer_list);
}

int	ft_nb_arg(t_lexer *lexer_list)
{
	int	i;

	i = 1;
	while (lexer_list && lexer_list->token != PIPE)
	{
		if (lexer_list->token == ARG)
			i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}

void	ft_bzero(pid_t *pid, int nb_node)
{
	while (nb_node-- > 0)
		*(pid++) = 0;
}

void	init_var(int *fd, int *y, int *wstatus)
{
	*wstatus = 0;
	y[0] = 0;
	y[1] = -1;
	fd[0] = 0;
	fd[1] = 0;
}
