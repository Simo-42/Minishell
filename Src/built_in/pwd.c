/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:49:05 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 00:50:05 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	get_pwd(char *tab)
{
	char	**str;

	str = ft_split(tab, ' ');
	if (tab && strcmp(str[0], "pwd") == 0)
	{
		if (str[1] == NULL)
			display_pwd();
		else
			display_pwd_error();
	}
	return (0);
}

void	display_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		ft_printf("error retrieving current directory: " \
		"No such file or directory\n");
		g_all.utils->err = 1;
		free(tmp);
		return ;
	}
	if (g_all.utils->node->out > 0)
	{
		ft_write_fd(tmp, g_all.utils->node->out);
		ft_write_fd("\n", g_all.utils->node->out);
	}
	else if (!g_all.utils->node->out_fail)
	{
		printf("%s\n", tmp);
	}
	g_all.utils->err = 0;
	free(tmp);
}

void	display_pwd_error(void)
{
	if (g_all.utils->node->out > 0)
	{
		ft_write_fd("pwd: too many arguments", g_all.utils->node->out);
	}
	else if (!g_all.utils->node->out_fail)
	{
		printf("pwd: too many arguments");
	}
	g_all.utils->err = 1;
}

void	find_old_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD", 6))
		{
			change_directory3(env);
			break ;
		}
		tmp = tmp->next;
	}
}
