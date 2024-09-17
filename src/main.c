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

void	algo_minishell(t_shelly *shelly)
{
	int	check;

	check = 0;
	check = ft_lexer(shelly);
	if (check == 0)
	{
		check = ft_parser(shelly);
		if (check == 0)
		{
			ft_exec(shelly->ast);
			free_ast(shelly->ast);
		}
	}
}

int	main(void)
{
	t_shelly	shelly;

	shelly.str = NULL;
	if (init_shelly(&shelly) == 0)
	{
		shelly.loop = 0;
		while (shelly.loop == 0)
		{
			shelly.cmd = readline("MINISHELL> ");
			if (!shelly.cmd)
				return (ft_error("Error launching shell", 0, 0));
			else
				add_history(shelly.cmd);
			if (ft_strncmp(shelly.cmd, "exit", 4) == 0)
				return (ft_error("Exiting shell", 0, 0));
			algo_minishell(&shelly);
			ft_free(&shelly);
		}
	}
	// system("leaks minishell");
}
