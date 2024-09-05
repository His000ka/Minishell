/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shelly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:25 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:51:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_env(char **envp, t_env *env)
{
	int	i;

	i = -1;
	while (envp[++i]);
	env->envp = malloc(sizeof(char *) * (i + 1));
	if (!env->envp)
		return (1);
	i = -1;
	while (envp[++i])
		env->envp[i] = ft_strdup(envp[i]);
	env->envp[i] = NULL;
	i = -1;
	// while (env->envp[++i] != NULL)
	// 	printf("%s\n", env->envp[i]);
	return (0);
}

int	init_shelly(char **envp, t_shelly *shelly)
{
	int	check;

	check = 0;
	shelly->env = malloc(sizeof(t_env));
	if (!shelly->env)
		return (ft_error("ERROR INIT\n", shelly));
	check += init_env(envp, shelly->env);
	if (check > 0)
		ft_error("ERROR INIT\n", shelly);
	return (check);
}
