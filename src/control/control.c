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
/*   Created: 2024/10/16 14:24:57 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/16 14:24:57 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	control_c(int sig)
{
	t_shelly	*shelly;

	(void)sig;
	shelly = get_shelly();
	if (shelly->process_running == 1)
		shelly->exit_code = 131;
	else
		shelly->exit_code = 1;
	shelly->ctrlc = 1;
	write(STDOUT_FILENO, "\nMINISHELL> ", 12);
	rl_on_new_line();
	rl_redisplay();
}

void	control_d(void)
{
	printf("exit\n");
	exit(131);
}

void	control_s(int sig)
{
	t_shelly	*shelly;

	(void)sig;
	shelly = get_shelly();
	if (shelly->process_running == 1)
		shelly->exit_code = 131;
	else
		shelly->exit_code = 0;
	shelly->ctrls = 1;
	rl_redisplay();
	write(STDOUT_FILENO, "\rMINISHELL> ", 12);
	rl_on_new_line();
}

void	control(void)
{
	signal(SIGQUIT, control_s);
	signal(SIGINT, control_c);
}
