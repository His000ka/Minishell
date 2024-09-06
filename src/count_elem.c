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

int	count_index(char *str)
{
	int	i;

	i = 0;
	while(str[i] == ' ')
		i++;
	if (str[i] == 34)
		while (str[++i] != 34);
	if (str[i] == 39)
		while (str[++i] != 39);
	return (i);
}

int	count_elem_4(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while (shelly->cmd[i])
	{
		i += count_index(&shelly->cmd[i]);
		while (ft_isprint(shelly->cmd[i]) == 1 && shelly->cmd[i] != ' ')
		{
			if (shelly->cmd[i] == '<' && shelly->cmd[i - 1] != '<' && ((shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] == ' ')
					|| (shelly->cmd[i - 1] == ' ' && shelly->cmd[i + 1] != ' ' && shelly->cmd[i + 1] != '<')))
				count += 1;
			if (shelly->cmd[i] == '<' && shelly->cmd[i - 1] != '<' && shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] != ' ' && shelly->cmd[i + 1] != '<')
				count += 2;
			if (shelly->cmd[i] == '<' && shelly->cmd[i - 1] == '<' && (shelly->cmd[i - 2] != ' ' || shelly->cmd[i + 1] != ' '))
			{
				if (shelly->cmd[i - 2] != ' ' && shelly->cmd[i + 1] != ' ')
					count += 1;
				count += 1;
			}
			i++;
		}
		while(shelly->cmd[i] == ' ')
			i++;
	}
	return (count);
}

int	count_elem_3(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while (shelly->cmd[i])
	{
		i += count_index(&shelly->cmd[i]);
		while (ft_isprint(shelly->cmd[i]) == 1 && shelly->cmd[i] != ' ')
		{
			if (shelly->cmd[i] == '>' && shelly->cmd[i - 1] != '>' && ((shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] == ' ')
					|| (shelly->cmd[i - 1] == ' ' && shelly->cmd[i + 1] != ' ' && shelly->cmd[i + 1] != '>')))
				count += 1;
			if (shelly->cmd[i] == '>' && shelly->cmd[i - 1] != '>' && shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] != ' ' && shelly->cmd[i + 1] != '>')
				count += 2;
			if (shelly->cmd[i] == '>' && shelly->cmd[i - 1] == '>' && (shelly->cmd[i - 2] != ' ' || shelly->cmd[i + 1] != ' '))
			{
				if (shelly->cmd[i - 2] != ' ' && shelly->cmd[i + 1] != ' ')
					count += 1;
				count += 1;
			}
			i++;
		}
		while(shelly->cmd[i] == ' ')
			i++;
	}
	return (count_elem_4(shelly, count));
}

int	count_elem_2(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while(shelly->cmd[i])
	{
		i += count_index(&shelly->cmd[i]);
		while (ft_isprint(shelly->cmd[i]) == 1 && shelly->cmd[i] != ' ')
		{
			if (shelly->cmd[i] == '|' && ((shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] == ' ')
					|| (shelly->cmd[i - 1] == ' ' && shelly->cmd[i + 1] != ' ')))
				count += 1;
			if (shelly->cmd[i] == '|' && shelly->cmd[i - 1] != ' ' && shelly->cmd[i + 1] != ' ')
				count += 2;
			i++;
		}
		while(shelly->cmd[i] == ' ')
			i++;
	}
	return (count_elem_3(shelly, count));
}

int	count_elem(t_shelly *shelly, int count)
{
	int	i;

	i = 0;
	while(shelly->cmd[i])
	{
		while(shelly->cmd[i] == ' ')
			i++;
		if (shelly->cmd[i] == 34 || shelly->cmd[i] == 39)
		{
			if (shelly->cmd[i] == 34)
				while (shelly->cmd[++i] != 34);
			if (shelly->cmd[i] == 39)
				while (shelly->cmd[++i] != 39);
			count++;
			i++;
		}
		if (ft_is_good_char(shelly->cmd[i]) == 1 && shelly->cmd[i] != ' ')
		{
			while (ft_is_good_char(shelly->cmd[i]) == 1 && shelly->cmd[i] != ' ')
				i++;
			count++;
		}
		while(shelly->cmd[i] == ' ')
			i++;
	}
	return (count_elem_2(shelly, count));
}
