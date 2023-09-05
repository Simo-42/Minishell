/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:36:52 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/24 16:51:24 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	get_in_fail(t_node *node, t_lexer *lexer_lst)
{
	if (!node->in_fail)
	{
		node->in = -2;
		perror(lexer_lst->next->word);
	}
	else
	{
		node->in = -2;
		ft_write_fd("bash: ambiguous redirect\n", 2);
	}
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	dest = ft_malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	has_cmd(t_lexer *lexer_lst)
{
	while (lexer_lst)
	{
		if (lexer_lst->token == CMD)
			return (1);
		lexer_lst = lexer_lst->next;
	}
	return (0);
}

int	nb_cmd(t_lexer *lexer_list)
{
	int	i;

	i = 0;
	while (lexer_list)
	{
		if (lexer_list->token == CMD)
			i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}

int	nb_node(t_lexer *lexer_list)
{
	int	i;

	i = 0;
	while (lexer_list)
	{
		if (lexer_list->token == PIPE || !lexer_list->next)
			i++;
		lexer_list = lexer_list->next;
	}
	return (i);
}
