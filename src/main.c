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
			ft_exec(shelly, shelly->ast);
			free_ast(shelly->ast);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shelly	shelly;

	shelly.str = NULL;
	shelly.env = NULL;
	(void)ac;
	(void)av;
	create_env_list(&shelly.env, envp);
	// control();
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
			algo_minishell(&shelly);
			ft_free(&shelly);
		}
	}
	free_env(&shelly);
	shelly.env = NULL;
	// system("leaks minishell");
}
