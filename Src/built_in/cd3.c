/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:40:33 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:45:43 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	change_directory(char *dir)
{
	if (chdir(dir) == -1)
	{
		perror("chdir");
		g_all.utils->err = 1;
		return (0);
	}
	return (1);
}

int	change_directory3(t_env *tmp)
{
	if (chdir(get_old_pwd(tmp) + 7) == -1)
	{
		perror("chdir");
		g_all.utils->err = 1;
		return (0);
	}
	return (1);
}

char	*get_pwd_env(t_env	*tmp)
{
	tmp = g_all.utils->env_lst;
	while (tmp)
	{
		if (!strncmp("PWD=", tmp->content, 4))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	verif_oldpwd(char *str)
{
	t_env	*tmp;
	char	*s1;

	tmp = g_all.utils->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "OLDPWD=",
				ft_strlen_eguale("OLDPWD=")) == 0)
		{
			s1 = ft_strjoin_2("OLDPWD=", str);
			tmp->content = var_exist(s1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
