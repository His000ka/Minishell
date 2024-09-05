/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:48:27 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:49:42 by pitroin          ###   ########.fr       */
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

void	ft_free_token(t_token *t)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = t;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		if (current_token->str)
			free(current_token->str);
		free(current_token);
		current_token = next_token;
	}
}

void	ft_free(t_shelly *shelly)
{
	int	i;

	if (shelly->str)
	{
		i = -1;
		while (shelly->str[++i])
			free(shelly->str[i]);
		free(shelly->str);
		shelly->str = NULL;
	}
	if (shelly->token && ft_strlen(shelly->cmd) > 0)
	{
		ft_free_token(shelly->token);
		shelly->token = NULL;
	}
	if (shelly->env != NULL)
	{
		if (shelly->env->envp != NULL)
			free_envp(shelly->env);
		free(shelly->env);
		shelly->env = NULL;
	}
	if (shelly->cmd != NULL)
	{
		free(shelly->cmd);
		shelly->cmd = NULL;
	}
}