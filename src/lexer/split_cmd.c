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
	if (is_quote(&shelly->cmd[res], 1) != 0)
		return (i - res - 2);
	else if (is_good_char(&shelly->cmd[res], 1) != 0)
		return (i - res);
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
	{
		if (is_quote(&shelly->cmd[res], 0) == 1)
			return (res + 1);
		return (res);
	}
	else if (ft_strncmp(str, "size", 4) == 0)
		return (size_elem(shelly, i, res));
	return (0);
}

int	add_elem(t_shelly *shelly, int count)
{
	int	size;
	int	j;
	int	i;
	int	k;

	j = 0;
	while (j < count)
	{
		size = info_elem(shelly, j, "size");
		shelly->str[j] = malloc(sizeof(char) * (size + 1));
		if (!shelly->str[j])
			return (1);
		i = info_elem(shelly, j, "index");
		k = -1;
		while (++k < size && shelly->cmd[k + i] != '\0')
			shelly->str[j][k] = shelly->cmd[k + i];
		shelly->str[j][k] = '\0';
		j++;
	}
	shelly->str[j] = NULL;
	return (0);
}

int	split_command(t_shelly *shelly)
{
	int	count;

	count = 0;
	count += count_elem(shelly, count);
	if (count == 0)
		return (1);
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return (1);
	if (add_elem(shelly, count) == 1)
		return (1);
	return (0);
}
