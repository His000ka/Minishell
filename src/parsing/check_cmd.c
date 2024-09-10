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

int	check_last_elem(t_shelly *shelly)
{
	int	i;

	i = -1;
	if (ft_strlen(shelly->cmd) == 0)
		return (1);
	if (shelly->cmd[0] == '|')
		return (ft_error(SYNTAX_ERROR, shelly->cmd[0], 1));
	while (shelly->cmd[++i])
		;
	i--;
	if (shelly->cmd[i] == '>' || shelly->cmd[i] == '<'
		|| shelly->cmd[i] == '|')
		return (ft_error(SYNTAX_ERROR, shelly->cmd[i], 1));
	return (0);
}

int	check_order(t_shelly *shelly, int check)
{
	int	i;

	i = -1;
	if (check > 0)
		return (0);
	while (shelly->cmd[++i])
	{
		if (shelly->cmd[i] == '|' && shelly->cmd[i + 1] == '|'
			&& shelly->cmd[i + 2] == '|')
			return (ft_error(SYNTAX_ERROR, shelly->cmd[i], 1));
		if (shelly->cmd[i] == '>' && shelly->cmd[i + 1] == '>'
			&& shelly->cmd[i + 2] == '>' && shelly->cmd[i + 3] == '>')
			return (ft_error(SYNTAX_ERROR, shelly->cmd[i], 2));
		if (shelly->cmd[i] == '>' && shelly->cmd[i + 1] == '>'
			&& shelly->cmd[i + 2] == '>')
			return (ft_error(SYNTAX_ERROR, shelly->cmd[i], 1));
	}
	return (0);
}

int	check_cmd(t_shelly *shelly)
{
	int	check;

	check = 0;
	check += check_quote(shelly);
	check += check_last_elem(shelly);
	check += check_order(shelly, check);
	// printf("check_cmd: %d\n", check);
	return (check);
}
