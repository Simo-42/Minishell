/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:33:25 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/10/15 11:16:09 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_all	g_all;

void	init_data(t_data *data, int ac, char **av, char **env)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->line = NULL;
	data->allcommand = NULL;
	data->envpaths = NULL;
	data->lexer_list = NULL;
	data->index = 0;
}

void	exit_error(char *str)
{
	ft_write_fd(str, 2);
	exit(1);
}

char	**get_new_env(t_env *env_lst)
{
	char	**new_env;
	int		i;
	t_env	*head;

	head = env_lst;
	i = 0;
	while (env_lst)
	{
		i++;
		env_lst = env_lst->next;
	}
	new_env = ft_malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	new_env[i] = NULL;
	env_lst = head;
	i = 0;
	while (env_lst)
	{
		new_env[i++] = env_lst->content;
		env_lst = env_lst->next;
	}
	env_lst = head;
	return (new_env);
}

void	prompt_loop(char *tmp, t_data data, char **env)
{
	t_lexer	*tmp_lex;
	char	**new_env;

	(void)env;
	if (!tmp)
		exit_all();
	if (tmp && tmp[0])
	{
		data.line = tmp;
		ft_lexer(&data);
		if (!ft_parser(&data))
		{
			g_all.utils->err = 2;
			return ;
		}
		tmp_lex = data.lexer_list;
		new_env = get_new_env(g_all.utils->env_lst);
		expand(data.quote, new_env, tmp_lex);
		if (tmp_lex && tmp_lex->word)
		{
			ft_init_exec(&data);
			ft_prep_exec(&data);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*tmp;

	if (!isatty(STDIN_FILENO))
	{
		ft_write_fd("minishell: stdin is not a tty", 2);
		exit(1);
	}
	if (ac != 1)
		exit_error("bad number of arguments");
	init_data(&data, ac, av, env);
	g_all.utils = init_env(env);
	tmp = NULL;
	g_all.utils->export_lst = NULL;
	while (42)
	{
		free(tmp);
		tmp = NULL;
		handle_sig();
		tmp = readline("minishell$ ");
		add_history(tmp);
		prompt_loop(tmp, data, env);
	}
}
