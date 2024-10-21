/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:40:26 by marvin            #+#    #+#             */
/*   Updated: 2024/09/06 11:40:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*double_quote(t_shelly *shelly, char *val, t_data_elem *data, char *res)
{
	data->i++;
	while (val[data->k + data->i] != 34)
	{
		if (val[data->k + data->i] == '$')
		{
			if (expender(shelly, data) == 1)
				return (NULL);
		}
		else
		{
			res[data->k] = val[data->k + data->i];
			data->k++;
		}
	}
	res[data->k] = '\0';
	data->i += data->k;
	return (res);
}

int	calc_size_quote(t_data_elem *data, char *val)
{
	data->size = 1;
	if (val[data->i] == 39)
	{
		while (val[data->i + data->size] != 39)
			data->size++;
	}
	if (val[data->i] == 34)
	{
		while (val[data->i + data->size] != 34)
			data->size++;
	}
	return (data->size);
}

char	*manage_quote(t_shelly *shelly, t_data_elem *data, char *val)
{
	char	*res;

	res = malloc(sizeof(char) * calc_size_quote(data, val));
	if (!res)
		return (NULL);
	data->k = 0;
	if (val[data->i] == 34)
		return (double_quote(shelly, val, data, res));
	if (val[data->i] == 39)
	{
		data->i++;
		while (val[data->k + data->i] != 39)
		{
			res[data->k] = val[data->k + data->i];
			data->k++;
		}
	}
	res[data->k] = '\0';
	data->i += data->k;
	return (res);
}

int	check_quote(t_shelly *shelly)
{
	int	i;

	i = -1;
	while (shelly->cmd[++i] != '\0')
	{
		if (shelly->cmd[i] == 34)
		{
			i++;
			while (shelly->cmd[i] != 34 && shelly->cmd[i] != '\0')
				i++;
			if (shelly->cmd[i] != 34)
				return (ft_error(NULL, 0, 0));
		}
		else if (shelly->cmd[i] == 39)
		{
			i++;
			while (shelly->cmd[i] != 39 && shelly->cmd[i] != '\0')
				i++;
			if (shelly->cmd[i] != 39)
				return (ft_error(NULL, 0, 0));
		}
	}
	return (0);
}
