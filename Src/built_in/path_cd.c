/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:30:19 by mhajji-b          #+#    #+#             */
/*   Updated: 2023/06/14 12:29:22 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

// int	verif_pwd(char *str)
// {
// 	t_env	*tmp;
// 	char	*s1;

// 	tmp = g_all.utils->env_lst;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->content, "PWD=", ft_strlen_eguale("PWD=")) == 0)
// 		{
// 			s1 = ft_strjoin_2("PWD=", str);
// 			tmp->content = var_exist(s1);
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// int	verif_oldpwd(char *str)
// {
// 	t_env	*tmp;
// 	char	*s1;

// 	tmp = g_all.utils->env_lst;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->content, "OLDPWD=",
// 				ft_strlen_eguale("OLDPWD=")) == 0)
// 		{
// 			s1 = ft_strjoin_2("OLDPWD=", str);
// 			tmp->content = var_exist(s1);
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

int	verif_oldpwd_export(char *str)
{
	t_export	*tmp;
	char		*s1;

	tmp = g_all.utils->export_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "OLDPWD=", ft_strlen_eguale("OLDPWD=")) == 0)
		{
			s1 = ft_strjoin_2("OLDPWD=", str);
			tmp->value = var_exist(s1);
			tmp->value = case_egale(s1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	verif_pwd_export(char *str)
{
	t_export	*tmp;
	char		*s1;

	tmp = g_all.utils->export_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD=", ft_strlen_eguale("PWD=")) == 0)
		{
			s1 = ft_strjoin_2("PWD=", str);
			tmp->value = var_exist(s1);
			tmp->value = case_egale(s1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
