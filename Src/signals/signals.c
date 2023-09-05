/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:32:56 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/07/10 13:29:25 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_all.utils->err = 130;
}

void	ctrl_c_handler_here_doc(int sig)
{
	(void)sig;
	close(0);
	write(2, "\n", 1);
	g_all.utils->is_here_doc = 0;
	g_all.utils->can_run = 0;
	g_all.utils->err = 130;
}

void	handle_sig(void)
{
	if (g_all.utils->is_here_doc)
		signal(SIGINT, &ctrl_c_handler_here_doc);
	else
	{
		signal(SIGINT, &ctrl_c_handler);
		signal(SIGQUIT, SIG_IGN);
	}	
}

void	sigint_process(int sig)
{
	(void)sig;
	g_all.utils->err = 130;
	ft_putchar('\n');
}

void	handle_process_signal(void)
{
	signal(SIGINT, &sigint_process);
	signal(SIGQUIT, &sigquit_process);
}
