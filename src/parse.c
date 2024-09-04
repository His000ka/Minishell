/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:07:44 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/04 11:14:20 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				return (1);
		}
		else if (shelly->cmd[i] == 39)
		{
			i++;
			while (shelly->cmd[i] != 39 && shelly->cmd[i] != '\0')
				i++;
			if (shelly->cmd[i] != 39)
				return (1);
		}
	}
	return (0);
}

void	ft_parse(t_shelly *shelly)
{
	if (check_quote(shelly) == 1)
		ft_error("FAIL QUOTE\n", shelly);
}