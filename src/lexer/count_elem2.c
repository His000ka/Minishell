/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:29:59 by marvin            #+#    #+#             */
/*   Updated: 2024/09/06 14:29:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//f == 0 => count_elem()
int	is_quote(char *str, int flag)
{
	int	i;

	i = 0;
	if ((str[i] == 34 || str[i] == 39) && str[i] != '\0')
	{
		if (str[i] == 34)
			while (str[++i] != 34)
				;
		if (str[i] == 39)
			while (str[++i] != 39)
				;
		if (flag == 0)
			return (1);
		if (flag == 1)
		{
			if (str[i + 1] == 34 || str[i + 1] == 39)
				return (i + is_quote(&str[i + 1], 1) + 1);
			return (i + is_good_char(&str[i + 1], 1) + 1);
		}
		return (i);
	}
	return (0);
}

int	is_good_char(char *str, int flag)
{
	int	i;

	i = 0;
	if (str[i] <= 32 || str[i] > 126
		|| str[i] == 34 || str[i] == 39
		|| str[i] == '\0')
		return (0);
	while (str[i] > 32 && str[i] <= 126
		&& str[i] != 34 && str[i] != 39
		&& str[i] != '\0')
	{
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && flag == 2)
			break ;
		i++;
	}
	if (flag == 0)
		return (1);
	if (flag == 3)
		return (i);
	return (i + is_quote(&str[i], 1));
}

int	is_pipe(char *str, int flag)
{
	int	i;

	i = 0;
	if (str[i] == '|')
	{
		if (flag == 1)
			return (1);
		if (ft_strlen(str) == 1)
			return (0);
		if (check_char(str[i - 1]) == 1
			&& check_char(str[i + 1]) == 1)
			return (0);
		if ((check_char(str[i - 1]) == 1 && check_char(str[i + 1]) == 0)
			|| (check_char(str[i - 1]) == 0
				&& check_char(str[i + 1]) == 1))
			return (1);
		if (check_char(str[i - 1]) == 0
			&& check_char(str[i + 1]) == 0)
			return (2);
	}
	return (0);
}

int	is_trunc(char *str, int flag)
{
	int	i;

	i = 0;
	if (str[i] == '>')
	{
		if (flag == 1)
			return (1 + is_trunc(&str[1], 1));
		if (ft_strlen(str) == 1)
			return (0);
		if (check_char(str[i - 1]) == 1 && check_char(str[i + 1]) == 1)
			return (0);
		if ((check_char(str[i - 1]) == 0 && check_char(str[i + 1]) == 1)
			|| (check_char(str[i - 1]) == 1 && check_char(str[i + 1]) == 0))
			return (1);
		if (check_char(str[i - 1]) == 0 && check_char(str[i + 1]) == 0)
			return (2);
		if (str[i - 1] == '>' && (check_char(str[i - 2]) == 0
				|| check_char(str[i + 1]) == 0))
		{
			if (check_char(str[i - 2]) == 0 && check_char(str[i + 1]) == 0)
				return (2);
			return (1);
		}
	}
	return (0);
}

int	is_input(char *str, int flag)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (flag == 1)
			return (1 + is_input(&str[1], 1));
		if (ft_strlen(str) == 1)
			return (0);
		if (check_char(str[i - 1]) == 1 && check_char(str[i + 1]) == 1)
			return (0);
		if ((check_char(str[i - 1]) == 0 && check_char(str[i + 1]) == 1)
			|| (check_char(str[i - 1]) == 1 && check_char(str[i + 1]) == 0))
			return (1);
		if (check_char(str[i - 1]) == 0 && check_char(str[i + 1]) == 0)
			return (2);
		if (str[i - 1] == '<' && (check_char(str[i - 2]) == 0
				|| check_char(str[i + 1]) == 0))
		{
			if (check_char(str[i - 2]) == 0 && check_char(str[i + 1]) == 0)
				return (2);
			return (1);
		}
	}
	return (0);
}
