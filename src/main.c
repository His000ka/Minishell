/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:02:29 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/03 15:53:27 by fimazouz         ###   ########.fr       */
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
		free(shelly.cmd);
	}
}
