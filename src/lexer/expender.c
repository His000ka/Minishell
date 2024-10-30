/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:58:08 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/22 13:19:43 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	char_expend(char c)
{
	if (c <= 32 || c > 126 || c == '>' || c == '<'
		|| c == '|' || c == '\'' || c == '\"' || c == '$')
		return (1);
	return (0);
}

char	*expende_value(char *value)
{
	char	*res;

	if (value)
		res = ft_strdup(value);
	else
		res = ft_strdup("");
	if (!res)
		return (NULL);
	return (res);
}

char	*expend_exit_code(t_shelly *shelly, t_data_elem *data, int f)
{
	if (f == 0)
		data->i++;
	return (ft_strdup(ft_itoa(shelly->exit_code)));
}

char	*get_value_env(t_shelly *shelly, char *path)
{
	t_env	*current;

	current = shelly->env;
	while (current)
	{
		if (ft_strcmp(current->content, path) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expender(t_shelly *shelly, t_data_elem *data, char *val, int f)
{
	char	*value;
	char	*path;
	char	*res;

	data->size = 0;
	path = NULL;
	data->i++;
	if (val[data->i - 1] == '$' && (char_expend(val[data->i]) == 1
			|| val[data->i] == '\0'))
		return (ft_strndup(&val[data->i - 1], 1));
	while (char_expend(val[data->i + data->size]) == 0
		&& val[data->i + data->size] != '\0')
		data->size++;
	path = ft_strndup(&val[data->i], data->size);
	if (!path)
		return (NULL);
	if (ft_strncmp(path, "?", 1) == 0)
		return (expend_exit_code(shelly, data, f));
	value = get_value_env(shelly, path);
	res = expende_value(value);
	free(path);
	data->i += data->size;
	return (res);
}
