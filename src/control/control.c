/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:24:57 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/16 14:24:57 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	control_c(int sig)
{
	t_shelly	*shelly;

	shelly = get_shelly();
	shelly->exit_code = 128 + sig;
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nMINISHELL> ", 12);
	rl_redisplay();
}

void	control_d(void)
{
	printf("exit\n");
	exit(131);
}

void control_s(int sig)
{
	t_shelly	*shelly;

	shelly = get_shelly();
	shelly->exit_code = 128 + sig;
	write(1, "\rMINISHELL> ", 12);
}

void	control(void)
{
	// signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, control_s);
	signal(SIGINT, control_c);
}
