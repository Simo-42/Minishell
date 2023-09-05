/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:31:58 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:46:15 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	verif_pwd(char *str)
{
	t_env	*tmp;
	char	*s1;

	tmp = g_all.utils->env_lst;
	if (str == NULL)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PWD=", ft_strlen_eguale("PWD=")) == 0)
		{
			s1 = ft_strjoin_2("PWD=", str);
			tmp->content = var_exist(s1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_home(t_env	*tmp)
{
	tmp = g_all.utils->env_lst;
	while (tmp)
	{
		if (!strncmp("HOME=", tmp->content, 5))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_old_pwd(t_env	*tmp)
{
	tmp = g_all.utils->env_lst;
	while (tmp)
	{
		if (!strncmp("OLDPWD=", tmp->content, 6))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	verif_home(char *str)
{
	t_env	*tmp;
	char	*s1;

	tmp = g_all.utils->env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "HOME=", ft_strlen_eguale("HOME=")) == 0)
		{
			s1 = ft_strjoin_2("HOME=", str);
			tmp->content = var_exist(s1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	change_directory2(t_env *tmp)
{
	if (chdir(get_home(tmp) + 5) == -1)
	{
		perror("chdir");
		g_all.utils->err = 1;
		return (0);
	}
	return (1);
}
