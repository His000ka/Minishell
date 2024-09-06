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

#include "../include/minishell.h"

//f == 0 => count_elem()
int	is_quote(t_shelly *shelly, int flag)
{
	int	i;

	i = 0;
	if (shelly->cmd[i] == 34 || shelly->cmd[i] == 39)
	{
		while (shelly->cmd[++i] != 34)
			;
		if (shelly->cmd[i] == 39)
			while (shelly->cmd[++i] != 39)
				;
		if (flag == 0)
			return (1);
		if (flag == 1)
			return (i + 1);
		return (i);
	}
	return (0);
}