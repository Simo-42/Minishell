/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:18:04 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/06/10 17:05:28 by mhajji-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	initialize_data(t_stringdata *data, char *str)
{
	data->len = ft_strlen(str);
	data->i = 0;
	data->j = 0;
	data->is_escaped = 0;
}

void	extract_within_quotes(t_stringdata *data, char *str)
{
	while (data->i < data->len && (str[data->i] != '\'' || data->is_escaped))
	{
		if (str[data->i] == '\\' && !data->is_escaped)
			data->is_escaped = 1;
		else
		{
			str[data->j] = str[data->i];
			data->j++;
		}
		data->i++;
		data->is_escaped = 0;
	}
}

void	extract_quotes(t_stringdata *data, char *str, char quote)
{
	while (data->i < data->len && (str[data->i] != quote || data->is_escaped))
	{
		if (str[data->i] == '\\' && !data->is_escaped)
			data->is_escaped = 1;
		else
		{
			str[data->j] = str[data->i];
			data->j++;
		}
		data->i++;
		data->is_escaped = 0;
	}
}

void	remove_single_quotes(char *str)
{
	t_stringdata	data;

	initialize_data(&data, str);
	while (data.i < data.len)
	{
		if (str[data.i] == '\'' && !data.is_escaped)
		{
			data.i++;
			extract_within_quotes(&data, str);
			data.i++;
		}
		else
		{
			str[data.j] = str[data.i];
			data.i++;
			data.j++;
		}
	}
	str[data.j] = '\0';
}

void	remove_double_quotes(char *str)
{
	t_stringdata	data;

	initialize_data(&data, str);
	while (data.i < data.len)
	{
		if (str[data.i] == '\"' && !data.is_escaped)
		{
			data.i++;
			extract_quotes(&data, str, '\"');
			data.i++;
		}
		else
		{
			str[data.j] = str[data.i];
			data.i++;
			data.j++;
		}
	}
	str[data.j] = '\0';
}
