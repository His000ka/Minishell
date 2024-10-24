/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:59:09 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/08 19:59:09 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_env_node(char *env_var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = ft_strsearch(env_var, '=', 1);
	new->value = ft_strsearch(env_var, '=', 0);
	if (new->value != NULL)
		new->type = 1;
	else
		new->type = 0;
	new->next = NULL;
	return (new);
}

void	add_node_env(t_env **list, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	increment_shlvl(t_shelly *shelly)
{
	t_env	*tmp;
	int		shlvl_value;
	char	*new_value;

	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->content, "SHLVL") == 0)
		{
			shlvl_value = (int)ft_atoi(tmp->value) + 1;
			free(tmp->value);
			new_value = ft_itoa(shlvl_value);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	add_new_env_var(shelly, ft_strdup("SHLVL"), ft_strdup("1"));
}

int	create_env_list(t_shelly *shelly, char **envp)
{
	t_env	*new;
	int		i;

	i = -1;
	while (envp[++i])
	{
		new = create_env_node(envp[i]);
		add_node_env(&shelly->env, new);
	}
	increment_shlvl(shelly);
	i = 0;
	while (envp[i] != NULL)
		i++;
	shelly->envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (1);
	i = -1;
	while (envp[++i] != NULL)
	{
		shelly->envp[i] = ft_strdup(envp[i]);
		if (!shelly->envp[i])
			return (1);
	}
	shelly->envp[i] = NULL;
	return (0);
}
