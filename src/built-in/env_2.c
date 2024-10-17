/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:12:33 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/18 01:16:15 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_env_vars(t_env *env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
			free(envp[i++]);
		free(envp);
	}
}

void	copy_env_to_envp(t_shelly *shelly)
{
	t_env	*tmp;
	int		i;

	tmp = shelly->env;
	i = 0;
	while (tmp)
	{
		shelly->envp[i] = ft_strjoin(tmp->content, "=");
		shelly->envp[i] = ft_strjoin_free(shelly->envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	shelly->envp[i] = NULL;
}

void	update_envp(t_shelly *shelly)
{
	int	size;

	size = count_env_vars(shelly->env);
	free_envp(shelly->envp);
	shelly->envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!shelly->envp)
		return ;
	copy_env_to_envp(shelly);
}
