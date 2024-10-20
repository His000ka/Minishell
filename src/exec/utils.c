/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:01:09 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/17 19:29:59 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_code_execve(t_shelly *shelly)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
		shelly->exit_code = WEXITSTATUS(status);
}
