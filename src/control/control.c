/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/08 19:58:04 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/08 19:58:04 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	control_c(int sig)
{
	(void)(sig);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell> ", 12);
	rl_redisplay();
}

void	control_d(void)
{
	printf("exit\n");
	exit(1);
}

void	control_backslash(int sig)
{
	(void)sig;
}

void	control(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}
