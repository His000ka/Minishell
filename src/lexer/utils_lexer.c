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