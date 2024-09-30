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

int	double_quote(t_shelly *shelly, t_data_elem *data)
{
	data->i++;
	while (shelly->cmd[data->k + data->i] != 34)
	{
		if (shelly->cmd[data->k + data->i] == '$')
		{
			if (expender(shelly, data) == 1)
				return (EXIT_FAILURE);
		}
		else
		{
			shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
			data->k++;
		}
	}
	return (EXIT_SUCCESS);
}

int	manage_quote(t_shelly *shelly, t_data_elem *data)
{
	if (shelly->cmd[data->k + data->i] == 34)
	{
		if (double_quote(shelly, data) == 1)
			return (EXIT_FAILURE);
	}
	if (shelly->cmd[data->k + data->i] == 39)
	{
		data->i++;
		while (shelly->cmd[data->k + data->i] != 39)
		{
			shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
			data->k++;
		}
	}
	data->i++;
	return(EXIT_SUCCESS);
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

int	check_cmd(t_shelly *shelly)
{
	int	check;

	check = 0;
	check += check_quote(shelly);
	// check += check_last_elem(shelly);
	// check += check_order(shelly, check);
	// printf("check_cmd: %d\n", check);
	return (check);
}
