/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:35:02 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/17 17:45:26 by pitroin          ###   ########.fr       */
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
		if(new->value != NULL)
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
	{
		*list = new;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*create_env_list(t_env **list, char **envp)
{
	t_env	*new;
	int i = 0;

	while (envp[i])
	{
		new = create_env_node(envp[i]);
		add_node_env(list, new);
		i++;
	}
	return (*list);
}
