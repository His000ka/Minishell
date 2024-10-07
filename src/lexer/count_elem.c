/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:36:57 by marvin            #+#    #+#             */
/*   Updated: 2024/09/06 11:36:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_char(char c)
{
	if (c == ' ' || c == 34 || c == 39)
		return (1);
	if (c == '>' || c == '<')
		return (2);
	return (0);
}

int	ft_ischar(int c)
{
	if (c > 32 && c <= 126 && c != '>' && c != '<')
		return (1);
	return (0);
}

int	count_index(char *str, int flag)
{
	int	i;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (flag == 1)
		return (i);
	if (str[i] == 34)
		while (str[++i] != 34)
			;
	if (str[i] == 39)
		while (str[++i] != 39)
			;
	return (i);
}

int	count_elem_2(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while (shelly->cmd[i] != '\0')
	{
		i += count_index(&shelly->cmd[i], 0);
		if (shelly->cmd[i] == '\0')
			return (count);
		if (i == 0 && (shelly->cmd[i] == '|' || shelly->cmd[i] == '>'
				|| shelly->cmd[i] == '<'))
		{
			i = count_index(&shelly->cmd[i + 1], 1) + 1;
			if (shelly->cmd[i] == '\0')
				return (count);
		}
		else
		{
			count += is_pipe(&shelly->cmd[i], 0);
			count += is_trunc(&shelly->cmd[i], 0);
			count += is_input(&shelly->cmd[i], 0);
		}
		i++;
	}
	return (count);
}

int	count_elem(t_shelly *shelly, int count)
{
	int	i;
	int	tmp;

	i = 0;
	while (shelly->cmd[i] != '\0')
	{
		i += count_index(&shelly->cmd[i], 1);
		if (shelly->cmd[i] == '\0')
			return (count_elem_2(shelly, count));
		tmp = i;
		i += is_quote(&shelly->cmd[i], 1);
		if (tmp == i)
			i += is_good_char(&shelly->cmd[i], 1);
		if (tmp == i)
			i++;
		else
			count++;
	}
	if (check_char(shelly->cmd[0]) == 2 && (ft_ischar(shelly->cmd[1]) == 1
			|| (check_char(shelly->cmd[1]) == 2
				&& ft_ischar(shelly->cmd[2]) == 1)))
		count++;
	return (count_elem_2(shelly, count));
}
