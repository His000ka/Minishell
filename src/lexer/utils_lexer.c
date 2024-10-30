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

char	*d_q_2(char *res, char *tmp, char *expend)
{
	char	*tmp2;

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
	return (res);
}

char	*double_quote(t_shelly *shelly, char *val, t_data_elem *data)
{
	char	*expend;
	char	*tmp;
	char	*res;

	data->i++;
	res = NULL;
	expend = NULL;
	while (val[data->i] != 34)
	{
		data->size = 0;
		while (val[data->i + data->size] != '$'
			&& val[data->i + data->size] != 34)
			data->size++;
		tmp = ft_strndup(&val[data->i], data->size);
		data->i += data->size;
		if (val[data->i] == '$')
			expend = expender(shelly, data, val, 0);
		else
			expend = ft_strdup("");
		res = d_q_2(res, tmp, expend);
	}
	if (!res)
		return (ft_strdup(""));
	return (res);
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

void	ft_free_tmp(char **tmp1, char **tmp2)
{
	if (*tmp1)
		free(*tmp1);
	free(*tmp2);
	*tmp2 = NULL;
}
