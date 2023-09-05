/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:32:05 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 16:41:33 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || !s1[i] || !s2[i])
		return (1);
	while (s1 && s2 && s1[i] && s2[i]
		&& s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	simu_echo(char **tab, int i)
{
	i = i + 2;
	if (g_all.utils->node->out > 0)
		write_echo(tab, i);
	else if (!g_all.utils->node->out_fail)
	{
		while (tab[i])
		{
			if (ft_strcmp(tab[i], "-n"))
			{
				printf("%s", tab[i]);
				if (tab[i + 1])
					printf(" ");
			}
			i++;
		}
	}
}

void	get_words(t_lexer *lexer_lst, char **tab, int *i)
{
	while ((lexer_lst) && (lexer_lst->token == CMD || lexer_lst->token == ARG))
	{
		tab[(*i)++] = lexer_lst->word;
		lexer_lst = lexer_lst->next;
	}
}

void	process_echo(char **tab, int i)
{
	int	j;

	j = 0;
	if (g_all.utils->node->out > 0)
	{
		if (procc_in_echo(tab, i, j) == -1)
			return ;
		ft_write_fd("\n", g_all.utils->node->out);
	}
	else
		process_echo_2(tab, i);
	g_all.utils->err = 0;
}

void	process_echo_2(char **tab, int i)
{
	int	j;

	j = 0;
	if (!g_all.utils->node->out_fail)
	{
		while (tab[i])
		{
			if (j)
				printf(" %s", tab[i++]);
			else
				printf("%s", tab[i++]);
			j++;
		}
		printf("\n");
	}
}
