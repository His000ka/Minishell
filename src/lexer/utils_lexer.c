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
	data->k = 0;
	printf("test c : %c\n", val[data->i]);
	while (val[data->i] != 34)
	{
		if (val[data->i] == '$')
		{
			if (expender(shelly, data) == 1)
				return (NULL);
		}
		else
		{
			res[data->i - 1] = val[data->i];
			data->i++;
		}
	}
	res[data->i - 1] = val[data->i + 1];
	printf("fin ici %d\n", data->i);
	return (res);
}

char	*manage_quote(t_shelly *shelly, t_data_elem *data, char *val)
{
	char	*res;
	int		i;

	printf("je passe ici %s et data.i %d\n", &val[data->i], data->i);
	data->size = ft_strlen(val) - 1;
	printf("SIZE: %d\n", data->size);
	res = malloc(sizeof(char) * data->size + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < data->i)
		res[i] = val[i];
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
