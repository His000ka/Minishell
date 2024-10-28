/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/18 15:24:02 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	affiche_export(t_shelly *shelly)
{
	t_env	*tmp;

	sort_env_list(shelly->env);
	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (tmp->type == 1)
			printf("declare -x %s=\"%s\"\n", tmp->content, tmp->value);
		else if (tmp->type == 0)
			printf("declare -x %s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	add_node_export(t_env *list, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (list == NULL)
		list = new;
	else
	{
		tmp = list;
		while (list->next)
			list = list->next;
		list->next = new;
		list = tmp;
	}
}

void	add_or_not(t_shelly *shelly, char *str)
{
	t_env	*export_str;
	t_env	*tmp;

	export_str = create_env_node(str);
	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (export_str->content && tmp->content
			&& ft_strcmp(export_str->content, tmp->content) == 0)
		{
			if (export_str->value)
			{
				if (!tmp->value || (tmp->value && ft_strcmp(export_str->value,
							tmp->value) != 0))
				{
					tmp->value = ft_strdup(export_str->value);
					tmp->type = 1;
				}
			}
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		add_node_env(&shelly->env, export_str);
}

void	update_existing_var(t_env *tmp, char *value)
{
	char	*new_value;

	if (tmp->value)
	{
		new_value = ft_strjoin(tmp->value, value);
		if (!new_value)
			return ;
		free(tmp->value);
		tmp->value = new_value;
	}
	else
	{
		tmp->value = ft_strdup(value);
		if (!tmp->value)
			return ;
	}
	tmp->type = 1;
}

void	add_new_env_var(t_shelly *shelly, char *key, char *value)
{
	t_env	*new_var;

	new_var = create_env_node(key);
	new_var->value = ft_strdup(value);
	if (!new_var->value)
		return ;
	new_var->type = 1;
	add_node_env(&shelly->env, new_var);
}
