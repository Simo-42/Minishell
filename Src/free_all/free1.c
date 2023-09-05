/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:56:20 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 13:05:29 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_exit_child(t_exec *utils, int *fd)
{
	int	k;

	k = utils->err;
	if (fd)
		close_pipe(fd);
	close_fd();
	ft_free_all();
	exit(k);
}

void	memory_check(void *add)
{
	t_memory	*mem;
	t_memory	*tmp;

	mem = malloc(sizeof(t_memory));
	if (!mem)
		return ;
	mem->add = add;
	mem->next = NULL;
	if (g_all.d_mem == NULL)
		g_all.d_mem = mem;
	else
	{
		tmp = g_all.d_mem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mem;
	}	
}

void	*ft_malloc(size_t size)
{
	void	*add;

	add = malloc(size);
	if (!add)
		return (NULL);
	memory_check(add);
	return (add);
}

void	ft_free(void *add)
{
	t_memory	*tmp;
	t_memory	*ex;
	t_memory	*next;

	tmp = g_all.d_mem;
	ex = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->add == add)
		{
			tmp->add = NULL;
			free(tmp->add);
			free(tmp);
			if (ex)
				ex->next = next;
			else
				g_all.d_mem = next;
			return ;
		}
		ex = tmp;
		tmp = tmp->next;
	}
}

void	ft_free_all(void)
{
	t_memory	*tmp;
	t_memory	*next;

	tmp = g_all.d_mem;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->add)
			free(tmp->add);
		free(tmp);
		tmp = next;
	}
}
