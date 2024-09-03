/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:02:29 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/03 17:36:46 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	t_shelly	shelly;
	shelly.loop = 0;
	while (shelly.loop == 0)
	{
		shelly.cmd = readline("MINISHELL> ");
		if (!shelly.cmd)
			shelly.loop = ft_error("Error launching shell");
		if(ft_strncmp(shelly.cmd, "exit", 4) == 0)
			shelly.loop = ft_error("Exiting minishell\n");
		add_history(shelly.cmd);
		ft_parse(&shelly);
		free(shelly.cmd);
	}
}
