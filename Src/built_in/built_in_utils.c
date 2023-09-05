/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:09:27 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/07/09 15:01:31 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest_start);
}

char	*add_quotes_string(char *str)
{
	size_t	len;
	char	*quoted_str;

	len = (size_t)ft_strlen(str);
	quoted_str = ft_malloc(sizeof(char)
			*(len + 3));
	if (!quoted_str)
		return (NULL);
	quoted_str[0] = '"';
	ft_strcpy(quoted_str + 1, str);
	quoted_str[len + 1] = '"';
	quoted_str[len + 2] = '\0';
	return (quoted_str);
}

char	*join_them(char *str, int i, int flag)
{
	char	*tmp;

	tmp = NULL;
	if (str[i + 1] == '\0' && flag == 1)
	{
		tmp = ft_substr((const char *)str,
				(unsigned int)i + 1, (size_t)ft_strlen(str));
		str = ft_substr(str, 0, (size_t)i + 1);
		tmp = add_quotes_string(tmp);
		str = ft_strjoin4(str, tmp);
	}
	else if (flag == 1)
	{
		tmp = ft_substr((const char *)str,
				(unsigned int)i + 1, (size_t)ft_strlen(str));
		str = ft_substr(str, 0, (size_t)i + 1);
		tmp = add_quotes_string(tmp);
		str = ft_strjoin4(str, tmp);
	}
	return (str);
}

char	*case_egale(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			flag++;
			break ;
		}
		i++;
	}
	str = join_them(str, i, flag);
	return (str);
}

void	exit_all(void)
{
	ft_write_fd("exit\n", 1);
	ft_free_all();
	exit(0);
}
