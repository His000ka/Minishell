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

void	manage_elem(t_shelly *shelly, t_data_elem *data)
{
	if (shelly->cmd[data->k + data->i] == 34
		|| shelly->cmd[data->k + data->i] == 39)
		manage_quote(shelly, data);
	else if (shelly->cmd[data->k + data->i] == '$')
		expender(shelly, data);
	else
	{
		shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
		data->k++;
	}
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
			return (1);
		data.i = info_elem(shelly, data.j, "index");
		data.k = 0;
		while (data.k < data.size && shelly->cmd[data.k + data.i] != '\0')
			manage_elem(shelly, &data);
		shelly->str[data.j][data.k] = '\0';
		data.j++;
	}
	shelly->str[data.j] = NULL;
	return (0);
}

int	split_command(t_shelly *shelly)
{
	int	count;

	count = 0;
	count += count_elem(shelly, count);
	printf("count : %d\n", count);
	if (count == 0)
		return (1);
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return (1);
	if (add_elem(shelly, count) == 1)
		return (1);
	return (0);
}
