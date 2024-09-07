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

#include "../include/minishell.h"

int	check_char(char c)
{
	if (c == ' ' || c == 34 || c == 39)
		return (1);
	if (c == '>' || c == '<')
		return (2);
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
		count += is_pipe(&shelly->cmd[i], 0);
		i += is_pipe(&shelly->cmd[i], 1);
		count += is_trunc(&shelly->cmd[i], 0);
		i += is_trunc(&shelly->cmd[i], 1);
		count += is_input(&shelly->cmd[i], 0);
		i += is_input(&shelly->cmd[i], 1);
		i++;
	}
	// printf("count2 :%d\n", count);
	return (count);
}

int	count_elem(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while (shelly->cmd[i])
	{
		i += count_index(&shelly->cmd[i], 1);
		count += is_quote(&shelly->cmd[i], 0);
		i += is_quote(&shelly->cmd[i], 1);
		count += is_good_char(&shelly->cmd[i], 0);
		i += is_good_char(&shelly->cmd[i], 2);
		i += count_index(&shelly->cmd[i], 1);
	}
	// printf("count1 :%d\n", count);
	return (count_elem_2(shelly, count));
}
