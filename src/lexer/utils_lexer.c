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

char	*double_quote(t_shelly *shelly, char *val, t_data_elem *data)
{
	char	*expend = NULL;
	char	*tmp;
	char	*tmp2;
	char	*res = NULL;

	data->i++;
	while (val[data->i] != 34)
	{
		data->size = 0;
		while (val[data->i + data->size] != '$'
			&& val[data->i + data->size] != 34)
			data->size++;
		tmp = ft_strndup(&val[data->i], data->size);
		data->i += data->size;
		if (val[data->i] == '$')
			expend = expender(shelly, data, val);
		else
			expend = ft_strdup("");
		if (res)
		{
			tmp2 = ft_strjoin(tmp, expend);
			free(tmp);
			free(expend);
			tmp = ft_strjoin(res, tmp2);
			res = ft_strdup(tmp);
			free(tmp);
			free(tmp2);
		}
		else
			res = ft_strjoin(tmp, expend);
	}
	if (!res)
		return (ft_strdup(""));
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

	data->k = 0;
	res = NULL;
	if (val[data->i] == 34)
		return (double_quote(shelly, val, data));
	if (val[data->i] == 39)
	{
		data->i++;
		while (val[data->k + data->i] != 39)
			data->k++;
		res = ft_strndup(&val[data->i], data->k);
	}
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
