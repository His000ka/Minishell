/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:02:29 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:50:00 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_shelly	shelly;

	shelly.str = NULL;
	(void)ac;
	(void)av;
	if (init_shelly(envp, &shelly) == 0)
	{
		shelly.loop = 0;
		while (shelly.loop == 0)
		{
			shelly.cmd = readline("MINISHELL> ");
			if (!shelly.cmd)
				shelly.loop += ft_error("Error launching shell", &shelly);
			else
				add_history(shelly.cmd);
			if(ft_strncmp(shelly.cmd, "exit", 4) == 0)
				shelly.loop += ft_error("Exiting shell", &shelly);
			ft_parse(&shelly);
			ft_free(&shelly);
		}
	}
	system("leaks minishell");
}
