/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:07:44 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/03 16:20:06 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_quote(t_shelly *shelly, int i)
{
	int	j;
	
	j = i;
	if (shelly->cmd[i] == 34 || shelly->cmd[j] == 39)
		return (0);
	while (shelly->cmd[j] != '\0')
	{
		if (shelly->cmd[j] == shelly->cmd[i])
			return (0);
	}
	return (1);
}

void	parse(t_shelly *shelly)
{
	int i;

	i = -1;
	while (shelly->cmd[++i] != '\0')
	{
		if (ft_quote(shelly, i) == 1)
			printf("ERROR GUILLEMET");
	}
}