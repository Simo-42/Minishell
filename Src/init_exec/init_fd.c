/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:59:15 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/24 16:51:09 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	get_in_hd(t_node *node, t_lexer *lex_lst)
{
	if (lex_lst && lex_lst->token == LESS_DBE \
	&& lex_lst->next->token == LIMITOR)
	{
		if (node->in > 0)
			close (node->in);
		ft_here_doc(node, lex_lst);
		if (!access(node->here_doc, F_OK))
		{
			node->in = open(node->here_doc, O_RDONLY);
			unlink(node->here_doc);
		}
		else
		{
			node->in = -2;
			unlink(node->here_doc);
			perror(node->here_doc);
		}
	}
}

void	get_in(t_node *node, t_lexer *lexer_lst)
{
	node->in = -1;
	node->in_fail = 0;
	while (lexer_lst && lexer_lst->token != PIPE)
	{
		if (lexer_lst && lexer_lst->token == LESS \
		&& lexer_lst->next->token == FD)
		{
			if (node->in > 0)
				close(node->in);
			if (!lexer_lst->next->word)
				node->in_fail = 1;
			if (lexer_lst->next->word && !access(lexer_lst->next->word, R_OK))
				node->in = open(lexer_lst->next->word, O_RDONLY);
			else
				get_in_fail(node, lexer_lst);
		}
		get_in_hd(node, lexer_lst);
		lexer_lst = lexer_lst->next;
	}
}

void	get_out_append(t_node *node, t_lexer *lex_lst, int *has_out)
{
	if (lex_lst && lex_lst->next && lex_lst->token == GR_DBE \
	&& lex_lst->next->token == FD)
	{
		if (node->out > 0)
			close (node->out);
		if (lex_lst->next->word)
			node->out = open(lex_lst->next->word, O_CREAT
					| O_RDWR | O_APPEND, 0644);
		else
		{
			ft_write_fd("bash: ambiguous redirect\n", 2);
			node->out_fail = 2;
		}
		if (node->out_fail != 2 && (node->out == -1
				|| !access(lex_lst->next->word, F_OK)))
			node->out_fail = 1;
		*has_out = 1;
	}
}

void	get_out_normal(t_node *node, t_lexer *lex_lst)
{
	if (lex_lst && lex_lst->next && lex_lst->token == GR \
	&& lex_lst->next->token == FD)
	{
		if (node->out > 0)
			close (node->out);
		if (lex_lst->next->word)
			node->out = open(lex_lst->next->word, O_CREAT
					| O_RDWR | O_TRUNC, 0644);
		else
		{
			ft_write_fd("bash: ambiguous redirect\n", 2);
			node->out_fail = 2;
		}
		if (node->out_fail != 2 && (node->out == -1
				|| !access(lex_lst->next->word, W_OK)))
			node->out_fail = 1;
		node->has_out = 1;
	}
}

void	get_out(t_node *node, t_lexer *lex_lst)
{
	node->has_out = 0;
	node->out = -1;
	node->out_fail = 0;
	while (lex_lst && lex_lst->token != PIPE)
	{
		get_out_normal(node, lex_lst);
		get_out_append(node, lex_lst, &node->has_out);
		if (node->has_out && node->out == -1
			&& node->in != -2 && node->out_fail != 2)
		{
			node->has_out = 0;
			perror("Outfile");
		}
		lex_lst = lex_lst->next;
	}
}
