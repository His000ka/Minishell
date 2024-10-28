/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shelly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:00:50 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/08 20:00:50 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_shelly(t_shelly *shelly, char **envp)
{
	shelly->str = NULL;
	if (create_env_list(shelly, envp) == 1)
		return (1);
	shelly->oldpwd_count = 0;
	shelly->token = NULL;
	shelly->cmd = NULL;
	shelly->ast = NULL;
	shelly->delimiter = NULL;
	shelly->exit_code = 0;
	shelly->ctrlc = 0;
	shelly->ctrls = 0;
	shelly->fd_in = -1;
	shelly->fd_out = -1;
	return (0);
}
