/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:30:27 by firdawssema       #+#    #+#             */
/*   Updated: 2024/09/17 13:10:43 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void control_c(int sig)
{
	(void)(sig);

	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell> ", 12);
	rl_redisplay();
}

void	control_d()
{
	printf("exit\n");
	exit(1);
}

void	control_backslash(int sig)
{
	(void)sig;
}

void	control()
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}
