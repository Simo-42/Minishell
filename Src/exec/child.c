/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:49:02 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/08/29 17:28:49 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	**get_path(t_env *env_lst)
{
	char	**path;

	path = NULL;
	if (!env_lst || !env_lst->content)
	{
		return (NULL);
	}
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->content, "PATH=", 5))
		{
			path = ft_split(env_lst->content + 5, ':');
			return (path);
		}
		env_lst = env_lst->next;
	}
	return (path);
}

char	*get_cmd_path(char *cmd, t_env *env_lst)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
	if (!cmd | !cmd[0])
		return (NULL);
	if (!access(cmd, X_OK))
		return (cmd);
	else if (access(cmd, X_OK) && *cmd == '/')
		return (NULL);
	path = get_path(env_lst);
	if (path)
	{
		while (path && path[++i])
		{
			tmp = ft_strjoin2(path[i], "/");
			tmp = ft_strjoin2(tmp, cmd);
			if (!access(tmp, F_OK))
				return (tmp);
		}	
	}
	return (NULL);
}

int	check_path_exec(t_lexer *lexer, t_exec utils)
{
	if (!get_cmd_path(lexer->word, utils.env_lst))
	{
		write(2, lexer->word, strlen2(lexer->word));
		write(2, ": command not found\n", 21);
		return (1);
	}
	return (0);
}

char	**get_arg(t_lexer *lexer_list)
{
	char	**arg;
	int		nb_arg;
	int		i;

	i = 0;
	nb_arg = ft_nb_arg(lexer_list);
	arg = ft_malloc(sizeof(char *) * (nb_arg + 1));
	arg[i] = lexer_list->word;
	while (lexer_list && lexer_list->token != ARG && lexer_list->token != PIPE)
		lexer_list = lexer_list->next;
	while (++i < nb_arg && lexer_list->token == ARG)
	{
		arg[i] = lexer_list->word;
		lexer_list = lexer_list->next;
	}
	arg[i] = NULL;
	return (arg);
}

pid_t	ft_child(t_lexer *lexer_list, int *fd, int count, t_exec utils)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return (0);
	}
	if (pid == 0)
	{
		child_of_chill(lexer_list, fd, count, utils);
	}
	return (pid);
}
