/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:58:08 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/18 12:29:30 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expende_2(t_shelly *shelly, t_data_elem *data, char *value)
{
	char	*test;
	int		i;

	i = -1;
	test = ft_strdup(shelly->str[data->j]);
	if (!test)
		return (EXIT_FAILURE);
	free(shelly->str[data->j]);
	data->size += ft_strlen(value);
	shelly->str[data->j] = malloc(sizeof(char) * (data->size + 1));
	if (!shelly->str[data->j])
		return (EXIT_FAILURE);
	while (++i < data->k)
		shelly->str[data->j][i] = test[i];
	while (*value)
	{
		shelly->str[data->j][data->k] = *value;
		data->k++;
		value++;
	}
	shelly->str[data->j][data->k] = '\0';
	free(test);
	return (EXIT_SUCCESS);
}

int	expend_not_path(t_shelly *shelly, t_data_elem *data)
{
	char	*test;
	int		i;

	i = -1;
	test = ft_strdup(shelly->str[data->j]);
	if (!test)
		return (EXIT_FAILURE);
	free(shelly->str[data->j]);
	shelly->str[data->j] = malloc(sizeof(char) * (data->size) + 1);
	if (!shelly->str[data->j])
		return (EXIT_FAILURE);
	while (++i < data->k && test[i] != '\0')
		shelly->str[data->j][i] = test[i];
	shelly->str[data->j][data->k] = '\0';
	free(test);
	return (EXIT_SUCCESS);
}

int	char_expend(char c)
{
	if (c <= 32 || c > 126 || c == '>' || c == '<'
		|| c == '|' || c == '\'' || c == '\"' || c == '$')
		return (1);
	return (0);
}

int	expende_value(t_shelly *shelly, t_data_elem *data, char *path, char *value)
{
	char	*exit_code;

	if (value)
	{
		if (expende_2(shelly, data, value) == 1)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(path, "?") == 0)
	{
		exit_code = ft_itoa(shelly->exit_code);
		if (expende_2(shelly, data, exit_code) == 1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (expend_not_path(shelly, data) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	expender(t_shelly *shelly, t_data_elem *data)
{
	char	*value;
	char	*path;
	int		size;
	int		start;

	start = data->k + data->i + 1;
	size = 0;
	path = NULL;
	
	shelly->str[data->j][data->k] = '\0';
	while (char_expend(shelly->cmd[start + size]) == 0
		&& shelly->cmd[start + size] != '\0')
		size++;
	path = ft_strndup(&shelly->cmd[start], size);
	if (!path)
		return (EXIT_FAILURE);
	value = getenv(path);
	data->size = data->size - ft_strlen(path) - 1;
	expende_value(shelly, data, path, value);
	free(path);
	data->i = start + size - data->k;
	return (EXIT_SUCCESS);
}
