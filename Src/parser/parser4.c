/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:30:52 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/20 21:31:20 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	stop_pand_slash(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[0] == c && str[1] == '\0'))
		{
			printf("salut\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_tiret(char *str)
{
	if (!stop_pand_slash(str, '/'))
	{
		printf ("bash: %s : is an empty directory\n", str);
		return (0);
	}
	return (1);
}

int	chevron_pipe(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i - 1] == '>' && str[i + 1] == '<')
			{
				write (2, "zsh: parse error near `|'\n", 27);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
