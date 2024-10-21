/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:58:08 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/21 18:01:02 by pitroin          ###   ########.fr       */
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

char	*expend_exit_code(t_shelly *shelly, t_data_elem *data)
{
	data->i++;
	return (ft_strdup(ft_itoa(shelly->exit_code)));
}

char	*expender(t_shelly *shelly, t_data_elem *data, char *val)
{
	char	*value;
	char	*path;
	char	*res;

	data->size = 0;
	data->i++;
	path = NULL;
	if (ft_strcmp(val, "$") == 0)
		return (ft_strdup(val));
	while (char_expend(val[data->i + data->size]) == 0
		&& val[data->i + data->size] != '\0')
		data->size++;
	path = ft_strndup(&val[data->i], data->size);
	if (!path)
		return (NULL);
	if (ft_strncmp(path, "?", 1) == 0)
		return (expend_exit_code(shelly, data));
	value = getenv(path);
	res = expende_value(value);
	free(path);
	data->i += data->size;
	return (res);
}
