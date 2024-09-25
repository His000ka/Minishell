/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:58:08 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/25 18:21:14 by pitroin          ###   ########.fr       */
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

void	expend_not_path(t_shelly *shelly, t_data_elem *data)
{
	char	*test;
	int		i;

	i = -1;
	test = ft_strdup(shelly->str[data->j]);
	if (!test)
		return ;
	free(shelly->str[data->j]);
	shelly->str[data->j] = malloc(sizeof(char) * (data->size) + 1);
	if (!shelly->str[data->j])
		return ;
	while (++i < data->k && test[i] != '\0')
		shelly->str[data->j][i] = test[i];
	shelly->str[data->j][data->k] = '\0';
	free(test);
	return ;
}

void	expender(t_shelly *shelly, t_data_elem *data)
{
	char	*value;
	char	*path;
	int		size;
	int		start;

	start = data->k + data->i + 1;
	size = 0;
	path = NULL;
	shelly->str[data->j][data->k] = '\0';
	while (check_char(shelly->cmd[start + size]) == 0
		&& shelly->cmd[start + size] != '\0')
		size++;
	path = ft_strndup(&shelly->cmd[start], size);
	value = getenv(path);
	if (value)
	{
		data->size = data->size - ft_strlen(path) + ft_strlen(value) - 1;
		expende_2(shelly, data, value);
	}
	else
	{
		data->size = data->size - ft_strlen(path) - 1;
		data->i = start + size - data->k;
		return (expend_not_path(shelly, data));
	}
	free(path);
	data->i = start + size - data->k;
}
