/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:04:41 by mhajji-b          #+#    #+#             */
/*   Updated: 2023/08/29 17:31:31 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	write_echo(char **tab, int i)
{
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "-n"))
		{
			ft_write_fd(tab[i], g_all.utils->node->out);
			if (tab[i + 1])
				ft_write_fd(" ", g_all.utils->node->out);
		}
		i++;
	}
}

int	procc_in_echo(char **tab, int i, int j)
{
	while (tab[i])
	{
		if (j)
		{
			if (ft_write_fd(" ", g_all.utils->node->out))
			{
				g_all.utils->err = 1;
				return (-1);
			}
			ft_write_fd(tab[i++], g_all.utils->node->out);
		}
		else
		{
			if (ft_write_fd(tab[i++], g_all.utils->node->out))
			{
				g_all.utils->err = 1;
				return (-1);
			}
			j++;
		}
	}
	return (0);
}

void	child_of_chill(t_lexer *lexer_list, int *fd, int count, t_exec utils)
{
	handle_in(utils, count);
	handle_out(utils, fd, count);
	if (is_built_in(lexer_list))
	{
		ft_exec_single_built_in(lexer_list, fd);
		ft_exit_child(g_all.utils, fd);
	}
	if (!slashinlex(lexer_list))
		exec_chemin(lexer_list);
	else if (!check_path_exec(lexer_list, utils))
	{
		if (execve(get_cmd_path(lexer_list->word, utils.env_lst), \
		get_arg(lexer_list), utils.env) == -1)
			perror(lexer_list->word);
	}
	g_all.utils->err = 127;
	ft_exit_child(g_all.utils, fd);
}

int	slashinlex(t_lexer *lexer)
{
	int		i;

	i = 0;
	while (lexer->word[i])
		if (lexer->word[i++] == '/')
			return (0);
	return (1);
}

void	exec_chemin(t_lexer *lexer)
{
	if (execve(lexer->word, \
		get_arg(lexer), g_all.utils->env) == -1)
		perror(lexer->word);
}
