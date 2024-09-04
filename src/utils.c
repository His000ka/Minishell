/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:05:23 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/04 12:26:36 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envp(t_env *env)
{
	int	i;

	i = -1;
	while (env->envp[++i] != NULL)
		free(env->envp[i]);
	free(env->envp);
}

int	ft_error(char *str, t_shelly *shelly)
{
	if(!str)
		return(0);
	write(1, str, ft_strlen(str));
	if (shelly->env != NULL)
	{
		if (shelly->env->envp != NULL)
			free_envp(shelly->env);
		free(shelly->env);
	}
	// if (shelly->cmd != NULL)
	// {
	// 	free(shelly->cmd);
	// 	shelly->cmd = NULL;
	// }
	return(1);
}
