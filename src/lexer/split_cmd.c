/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:51 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/10 13:15:55 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_heredoc(t_shelly *shelly, t_data_elem *data)
{
	int	i;

	i = data->k + data->i;
	if (shelly->cmd[data->k + data->i] == '$')
	{
		if (shelly->cmd[i] == shelly->cmd[0])
			return (0);
		i--;
		while (shelly->cmd[i] != shelly->cmd[0]
			&& shelly->cmd[i] == ' ')
			i--;
		if (shelly->cmd[i] == '<' && shelly->cmd[i] != shelly->cmd[0])
		{
			i--;
			if (shelly->cmd[i] == '<')
				return (1);
		}
		return (0);
	}
	return (1);
}

int	add_elem(t_shelly *shelly, int count)
{
	t_data_elem	data;

	data.j = 0;
	while (data.j < count)
	{
		data.size = info_elem(shelly, data.j, "size");
		shelly->str[data.j] = malloc(sizeof(char) * (data.size + 1));
		if (!shelly->str[data.j])
			return (EXIT_FAILURE);
		data.i = info_elem(shelly, data.j, "index");
		data.k = 0;
		while (data.k < data.size && shelly->cmd[data.k + data.i] != '\0')
		{
			shelly->str[data.j][data.k] = shelly->cmd[data.k + data.i];
			data.k++;
		}
		shelly->str[data.j][data.k] = '\0';
		data.j++;
	}
	shelly->str[data.j] = NULL;
	return (EXIT_SUCCESS);
}

int	split_command(t_shelly *shelly)
{
	int	count;

	count = 0;
	count += count_elem(shelly, count);
	if (count == 0)
		return (EXIT_FAILURE);
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return (EXIT_FAILURE);
	if (add_elem(shelly, count) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
