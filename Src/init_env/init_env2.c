/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:38:04 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:38:35 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

t_env	*ft_get_env_lst_i(t_env *final)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	tmp = ft_strjoin_2("OLDPWD=", tmp);
	malloc_single_node(tmp, &final);
	return (final);
}

t_exec	*init_env(char **env)
{
	t_exec	*utils;

	utils = ft_malloc(sizeof(t_exec));
	if (!utils)
		return (NULL);
	utils->env_lst = NULL;
	if (env)
		utils->env_lst = ft_get_env_lst(env);
	utils->head_env_lst = utils->env_lst;
	utils->err = 0;
	utils->ret = 0;
	utils->is_here_doc = 0;
	return (utils);
}
