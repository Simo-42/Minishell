/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:39:45 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 15:01:27 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	ft_read_input(t_node *node, t_lexer *lexer_lst)
{
	g_all.utils->dupin = dup(0);
	while (42)
	{
		g_all.utils->hd = readline("> ");
		if (!g_all.utils->hd && g_all.utils->can_run)
		{
			write (2, "bash: warning: here-document delimited " \
			"by end-of-file (wanted `EOF')\n", 70);
			break ;
		}
		if (!g_all.utils->can_run)
		{
			dup2(g_all.utils->dupin, 0);
			break ;
		}
		if (!ft_strncmp(lexer_lst->next->word, g_all.utils->hd, \
		strlen2(lexer_lst->next->word)))
			if (strlen2(lexer_lst->next->word) == strlen2(g_all.utils->hd))
				break ;
		ft_write_fd(g_all.utils->hd, node->here_doc_fd);
		ft_write_fd("\n", node->here_doc_fd);
		free(g_all.utils->hd);
	}	
	close(g_all.utils->dupin);
	free(g_all.utils->hd);
}

void	ft_here_doc(t_node *node, t_lexer *lexer_lst)
{
	g_all.utils->is_here_doc = 1;
	handle_sig();
	node->here_doc = "here_doc.tmp";
	node->here_doc_fd = open(node->here_doc, O_CREAT | O_WRONLY | O_TRUNC,
			0777);
	if (node->here_doc_fd < 0)
		return ;
	ft_read_input(node, lexer_lst);
	g_all.utils->is_here_doc = 0;
	handle_sig();
	close(node->here_doc_fd);
}
