/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:21:36 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/22 12:39:14 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_mult_pipe(t_token *tmp)
{
	int		count;

	count = 0;
	while (tmp && tmp->type == PIPE)
	{
		tmp = tmp->next;
		count++;
		if (count == 3)
			return (ft_error(SYNTAX_ERROR, '|', 2));
	}
	if (count > 1)
		return (ft_error(SYNTAX_ERROR, '|', 1));
	return (0);
}

int	check_mult_r(t_token *tmp)
{
	int		count;

	count = 0;
	while (tmp->str[count] == '>')
	{
		count++;
		if (count == 4)
			return (ft_error(SYNTAX_ERROR, '>', 2));
	}
	if (count == 3)
		return (ft_error(SYNTAX_ERROR, '>', 1));
	return (0);
}

int	check_mult_l(t_token *tmp)
{
	int		count;

	count = 0;
	while (tmp->str[count] == '<')
	{
		count++;
		if (count == 4)
			return (ft_error(SYNTAX_ERROR, '<', 2));
	}
	if (count == 3)
		return (ft_error(SYNTAX_ERROR, '<', 1));
	return (0);
}

int	check_mult_token(t_shelly *shelly, t_token *token)
{
	int		check;
	t_token	*tmp;

	tmp = token;
	check = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			check += check_mult_pipe(tmp);
		if (tmp->type == CMD && tmp->str[0] == '>')
			check += check_mult_r(tmp);
		if (tmp->type == CMD && tmp->str[0] == '<')
			check += check_mult_l(tmp);
		if (check != 0)
		{
			shelly->exit_code = 258;
			return (check);
		}
		tmp = tmp->next;
	}
	return (0);
}
