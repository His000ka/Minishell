/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:58:08 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/21 17:03:10 by pitroin          ###   ########.fr       */
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
	{
		printf("value: %s\n", value);
		res = ft_strdup(value);
	}
	else
	{
		printf("ICIIIII?\n");
		res = ft_strdup("");
	}
	if (!res)
		return (NULL);
	return (res);
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
	{
		res = ft_strdup(ft_itoa(shelly->exit_code));
		if (!res)
			return (NULL);
		return (res);
	}
	printf("PATH: %s\n", path);
	value = getenv(path);
	res = expende_value(value);
	free(path);
	data->i += data->size;
	printf("data.i ap expend: %d\n", data->i);
	return (res);
}


// int	expende_2(t_shelly *shelly, t_data_elem *data, char *value)
// {
// 	char	*test;
// 	int		i;

// 	i = -1;
// 	test = ft_strdup(shelly->str[data->j]);
// 	if (!test)
// 		return (EXIT_FAILURE);
// 	free(shelly->str[data->j]);
// 	data->size += ft_strlen(value);
// 	shelly->str[data->j] = malloc(sizeof(char) * (data->size + 1));
// 	if (!shelly->str[data->j])
// 		return (EXIT_FAILURE);
// 	while (++i < data->k)
// 		shelly->str[data->j][i] = test[i];
// 	while (*value)
// 	{
// 		shelly->str[data->j][data->k] = *value;
// 		data->k++;
// 		value++;
// 	}
// 	shelly->str[data->j][data->k] = '\0';
// 	free(test);
// 	return (EXIT_SUCCESS);
// }

// int	expend_not_path(t_shelly *shelly, t_data_elem *data)
// {
// 	char	*test;
// 	int		i;

// 	i = -1;
// 	test = ft_strdup(shelly->str[data->j]);
// 	if (!test)
// 		return (EXIT_FAILURE);
// 	free(shelly->str[data->j]);
// 	shelly->str[data->j] = malloc(sizeof(char) * (data->size) + 1);
// 	if (!shelly->str[data->j])
// 		return (EXIT_FAILURE);
// 	while (++i < data->k && test[i] != '\0')
// 		shelly->str[data->j][i] = test[i];
// 	shelly->str[data->j][data->k] = '\0';
// 	free(test);
// 	return (EXIT_SUCCESS);
// }

// int	char_expend(char c)
// {
// 	if (c <= 32 || c > 126 || c == '>' || c == '<'
// 		|| c == '|' || c == '\'' || c == '\"' || c == '$')
// 		return (1);
// 	return (0);
// }

// int	expende_value(t_shelly *shelly, t_data_elem *data, char *path, char *value)
// {
// 	char	*exit_code;

// 	if (value)
// 	{
// 		if (expende_2(shelly, data, value) == 1)
// 			return (EXIT_FAILURE);
// 	}
// 	else if (ft_strcmp(path, "?") == 0)
// 	{
// 		exit_code = ft_itoa(shelly->exit_code);
// 		if (expende_2(shelly, data, exit_code) == 1)
// 			return (EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		if (expend_not_path(shelly, data) == 1)
// 			return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	expender(t_shelly *shelly, t_data_elem *data)
// {
// 	char	*value;
// 	char	*path;
// 	int		size;
// 	int		start;

// 	start = data->k + data->i + 1;
// 	size = 0;
// 	path = NULL;
// 	shelly->str[data->j][data->k] = '\0';
// 	while (char_expend(shelly->cmd[start + size]) == 0
// 		&& shelly->cmd[start + size] != '\0')
// 		size++;
// 	path = ft_strndup(&shelly->cmd[start], size);
// 	if (!path)
// 		return (EXIT_FAILURE);
// 	value = getenv(path);
// 	data->size = data->size - ft_strlen(path) - 1;
// 	expende_value(shelly, data, path, value);
// 	free(path);
// 	data->i = start + size - data->k;
// 	return (EXIT_SUCCESS);
// }
