/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
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
		//affiche_token(shelly);
		check = ft_parser(shelly);
		if (check == 0)
		{
			check = exec_heredoc(shelly, shelly->ast);
			if (check == 0)
				ft_exec(shelly, shelly->ast);
			free_ast(shelly->ast);
		}
	}
}

t_shelly	*get_shelly(void)
{
	static t_shelly	shelly;

	return (&shelly);
}

void	not_shelly_cmd(t_shelly *shelly)
{
	if (shelly->ctrlc == 0 || shelly->ctrls == 0)
		return (control_d());
	else
	{
		shelly->ctrlc = 0;
		shelly->ctrls = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shelly	*shelly;

	shelly = get_shelly();
	(void)ac;
	(void)av;
	control();
	if (init_shelly(shelly, envp) == 0)
	{
		shelly->loop = 0;
		while (shelly->loop == 0)
		{
			shelly->cmd = readline("MINISHELL> ");
			if (!shelly->cmd)
				not_shelly_cmd(shelly);
			else
			{
				add_history(shelly->cmd);
				algo_minishell(shelly);
				ft_free(shelly);
			}
		}
	}
	free_env(shelly);
	shelly->env = NULL;
}
