/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:11:16 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:38:43 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_env	*ft_new_env(char *env)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = ft_strdup(env);
	new->next = NULL;
	return (new);
}

void	ft_envlst_add_back(t_env *lst, t_env *new)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	malloc_single_node(char *str, t_env **env)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("Erreur lors de l'allocation de mémoire");
		return ;
	}
	new_node->content = ft_strdup(str);
	new_node->next = NULL;
	*env = new_node;
}

t_env	*ft_get_env_lst(char **env)
{
	int		env_size;
	int		i;
	t_env	*new;
	t_env	*final;

	i = -1;
	new = NULL;
	final = NULL;
	env_size = ft_env_size(env);
	if (env_size == 0)
	{
		final = ft_get_env_lst_i(final);
		return (final);
	}
	while (++i < env_size)
	{
		new = ft_new_env(env[i]);
		if (!final)
			final = new;
		else
			ft_envlst_add_back(final, new);
	}
	return (final);
}
