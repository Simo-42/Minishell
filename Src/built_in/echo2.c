/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:34:04 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 15:52:57 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	simulate_echo(t_lexer *lexer_lst)
{
	int			i;
	char		**tab;
	t_lexer		*head;

	i = 0;
	tab = NULL;
	head = lexer_lst;
	while ((lexer_lst) && (lexer_lst->token == CMD || lexer_lst->token == ARG))
	{
		lexer_lst = lexer_lst->next;
		i++;
	}
	tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return ;
	lexer_lst = head;
	i = 0;
	get_words(lexer_lst, tab, &i);
	tab[i] = NULL;
	simulate_echo_3(tab);
}

int	ft_truc(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] && str[i] != 'n')
		return (0);
	return (i);
}

void	simulate_echo_3(char **tab)
{
	int	i;
	int	ncount;

	i = 0;
	if (tab && tab[i] && tab[i + 1])
		ncount = ft_truc(tab[i + 1]);
	if (tab[i] && tab[i + 1] && !ft_strcmp(tab[i], "echo")
		&& tab[i + 1][0] != '-' && tab[i + 1][1] != 'n')
		process_echo(tab, ++i);
	else if (tab[i] && tab[i + 1] && !ft_strcmp(tab[i], "echo")
		&& ncount)
		simu_echo(tab, i);
	else
	{
		if (g_all.utils->node->out > 0)
			ft_write_fd("\n", g_all.utils->node->out);
		else
			printf("\n");
	}
}
