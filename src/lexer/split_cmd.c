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

int	size_elem(t_shelly *shelly, int i, int res)
{
	int	s;

	s = 0;
	if (is_quote(&shelly->cmd[res], 1) != 0)
		return (i - res - 2);
	else if (is_good_char(&shelly->cmd[res], 1) != 0)
	{
		s = is_good_char(&shelly->cmd[res], 3);
		if (shelly->cmd[s] == 34
			|| shelly->cmd[s] == 39)
			return (i - res - 2);
		return (i - res);
	}
	return (1);
}

int	browse_elem(t_shelly *shelly, int i, int res)
{
	i += is_quote(&shelly->cmd[i], 1);
	if (i == res)
		i += is_good_char(&shelly->cmd[i], 2);
	if (i == res)
		i += is_pipe(&shelly->cmd[i], 1);
	if (i == res)
		i += is_input(&shelly->cmd[i], 1);
	if (i == res)
		i += is_trunc(&shelly->cmd[i], 1);
	return (i);
}

int	info_elem(t_shelly *shelly, int j, char *str)
{
	int	i;
	int	res;
	int	count;

	i = 0;
	count = -1;
	while (++count <= j && shelly->cmd[i] != '\0')
	{
		i += count_index(&shelly->cmd[i], 1);
		res = i;
		i = browse_elem(shelly, i, res);
	}
	if (ft_strncmp(str, "index", 6) == 0)
		return (res);
	else if (ft_strncmp(str, "size", 4) == 0)
		return (size_elem(shelly, i, res));
	return (0);
}

int	double_quote(t_shelly *shelly, t_data_elem *data)
{
	int	tmp;

	tmp = data->i;
	if (shelly->cmd[data->i] == 34)
	{
		while (shelly->cmd[data->i] != 34)
			data->i++;
		if (shelly->cmd[data->i] == '|' || shelly->cmd[data->i] == '>'
			|| shelly->cmd[data->i] == '<' || shelly->cmd[data->i] == ' ')
			return (1);
		else
		{
			printf("ici\n");
			while (data->k < data->size && shelly->cmd[data->k + tmp] != '\0')
			{
				if (shelly->cmd[data->k + tmp] != 34)
				{
					shelly->str[data->j][data->k] = shelly->cmd[data->k + tmp];
					data->k++;
				}
				else
					tmp++;
			}
			shelly->str[data->j][data->k] = '\0';
		}
		return (0);
	}
	return (1);
}

void	expender(t_shelly *shelly, t_data_elem *data)
{
	printf("fck; %c\n", shelly->cmd[data->k + data->i]);
	if (shelly->cmd[data->k + data->i] == 34)
	{
		printf("exp\n");
		data->i++;
		while (shelly->cmd[data->k + data->i] != 34)
		{
			shelly->str[data->j][data->k] = shelly->cmd[data->k + data->i];
			data->k++;
		}
		data->i++;
	}
	// data->k++;
}

int	add_elem(t_shelly *shelly, int count)
{
	t_data_elem	data;

	data.j = 0;
	while (data.j < count)
	{
		data.size = info_elem(shelly, data.j, "size");
		printf("size: %d\n", data.size);
		shelly->str[data.j] = malloc(sizeof(char) * (data.size + 1));
		if (!shelly->str[data.j])
			return (1);
		data.i = info_elem(shelly, data.j, "index");
		printf("i: %d\n", data.i);
		data.k = 0;
		if (double_quote(shelly, &data) == 1)
		{
			while (data.k < data.size && shelly->cmd[data.k + data.i] != '\0')
			{
				if (shelly->cmd[data.k + data.i] == 34
					|| shelly->cmd[data.k + data.i] == 39)
						expender(shelly, &data);
				else
				{
					shelly->str[data.j][data.k] = shelly->cmd[data.k + data.i];
					data.k++;
				}
			}
			shelly->str[data.j][data.k] = '\0';
		}
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
	// if (count == 1)
	// {
	// 	printf("test");
	// 	return (1);
	// }
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return (1);
	if (add_elem(shelly, count) == 1)
		return (1);
	return (0);
}
