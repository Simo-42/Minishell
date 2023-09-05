/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:48:18 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 13:01:48 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	is_built_in(t_lexer *lexer_lst)
{
	if (lexer_lst->word == NULL)
		return (0);
	if (!ft_strncmp(lexer_lst->word, "pwd", 3))
		if (strlen2(lexer_lst->word) == 3)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "echo", 4))
		if (strlen2(lexer_lst->word) == 4)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "env", 3))
		if (strlen2(lexer_lst->word) == 3)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "unset", 5))
		if (strlen2(lexer_lst->word) == 5)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "cd", 2))
		if (strlen2(lexer_lst->word) == 2)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "export", 6))
		if (strlen2(lexer_lst->word) == 6)
			return (1);
	if (!ft_strncmp(lexer_lst->word, "exit", 4))
		if (strlen2(lexer_lst->word) == 4)
			return (1);
	return (0);
}

void	ft_exec_single_built_in(t_lexer *lexer_lst, int *fd)
{
	if (!ft_strncmp(lexer_lst->word, "export", 6))
		if (strlen2(lexer_lst->word) == 6)
			export_things(lexer_lst);
	if (!ft_strncmp(lexer_lst->word, "pwd", 3))
		if (strlen2(lexer_lst->word) == 3)
			get_pwd(lexer_lst->word);
	if (!ft_strncmp(lexer_lst->word, "echo", 4))
		if (strlen2(lexer_lst->word) == 4)
			simulate_echo(lexer_lst);
	if (!ft_strncmp(lexer_lst->word, "cd", 2))
		if (strlen2(lexer_lst->word) == 2)
			get_cd(lexer_lst);
	if (!ft_strncmp(lexer_lst->word, "env", 3))
		if (strlen2(lexer_lst->word) == 3)
			unset_things(lexer_lst);
	if (!ft_strncmp(lexer_lst->word, "unset", 5))
		if (strlen2(lexer_lst->word) == 5)
			unset_things(lexer_lst);
	if (!ft_strncmp(lexer_lst->word, "exit", 4))
		if (strlen2(lexer_lst->word) == 4)
			ft_exit(lexer_lst, fd);
	if (g_all.utils->node->out > 0)
		close(g_all.utils->node->out);
	lexer_lst = g_all.utils->head_lexer_lst;
}

int	start_exec(int *fd, pid_t *pid, t_lexer *lex_lst, int *y)
{
	lex_lst = g_all.utils->head_lexer_lst;
	while (g_all.utils->node && g_all.utils->node->has_cmd == 1 \
	&& ++y[1] >= 0 && g_all.utils->can_run)
	{
		while (lex_lst && lex_lst->token != CMD)
			lex_lst = lex_lst->next;
		g_all.utils->previous_fd = fd[0];
		if (g_all.utils->nb_cmd >= 1 && pipe(fd) < 0)
			return (0);
		if (g_all.utils->node->in != -2 && g_all.utils->node->out_fail != 2)
		{
			if ((is_built_in(lex_lst)) && g_all.utils->nb_cmd == 1)
				ft_exec_single_built_in(lex_lst, fd);
			else
				pid[y[0]++] = ft_child(lex_lst, fd, y[1], *(g_all.utils));
		}
		lex_lst = go_next_cmd(lex_lst);
		if (fd[1] > 0)
			close(fd[1]);
		if (g_all.utils->previous_fd > 0)
			close(g_all.utils->previous_fd);
		g_all.utils->node = g_all.utils->node->next;
	}
	close_pipe(fd);
	return (1);
}

void	ft_prep_exec(t_data *data)
{
	int		wstatus;
	pid_t	*pid;
	int		fd[2];
	int		y[2];

	init_var(fd, y, &wstatus);
	pid = ft_malloc(sizeof(pid_t) * (g_all.utils->nb_node));
	if (!pid)
		return ;
	ft_bzero(pid, g_all.utils->nb_node);
	handle_process_signal();
	if (!start_exec(fd, pid, data->lexer_list, y))
		perror("Pipe ");
	if (is_built_in(data->lexer_list) && g_all.utils->nb_cmd == 1 && close_fd())
		return ;
	y[0] = 0;
	while (--g_all.utils->nb_node >= 0 && \
	g_all.utils->can_run && g_all.utils->nb_cmd)
	{
		if (pid && pid[y[0]])
			waitpid(pid[y[0]++], &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_all.utils->err = WEXITSTATUS(wstatus);
	}
	close_fd();
}
