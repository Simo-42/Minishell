/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:20:02 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/21 00:21:25 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	verif_var_exist_export(t_exec *utils, char *str)
{
	t_export	*tmp;

	tmp = utils->export_lst;
	while (tmp)
	{
		if (tmp->value && ((ft_strncmp(tmp->value, str, \
			ft_strlen_eguale(tmp->value))) == 0 \
				&& (ft_strlen_eguale(str) == ft_strlen_eguale(tmp->value))))
		{
			if (verif_equal(str, '=')
				&& (ft_strlen_eguale(str) == ft_strlen_eguale(tmp->value)))
			tmp->value = case_egale(str);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	verif_equal(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	verif_var_exist(t_exec *utils, char *str)
{
	t_env	*tmp;

	tmp = utils->env_lst;
	while (tmp)
	{
		if (tmp->content && !(ft_strncmp
				(tmp->content, str, ft_strlen_eguale(tmp
						->content))) && (ft_strlen_eguale
				(str) == ft_strlen_eguale(tmp->content)))
		{
			tmp->content = str;
			tmp = utils->env_lst;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	verif_var_exist_export_2(t_exec *utils, char *str)
{
	t_export	*tmp;

	tmp = utils->export_lst;
	while (tmp)
	{
		if (tmp->value && ((ft_strncmp(tmp->value, str, \
		ft_strlen_eguale(tmp->value))) == 0 \
		&& (ft_strlen_eguale(str) == ft_strlen_eguale(tmp->value))))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
