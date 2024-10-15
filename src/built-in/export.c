/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/14 13:47:23 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char *str)
{
	if (ft_strcmp(str, "export") == 0)
		return (1);
	return (0);
}

void	affiche_export(t_shelly *shelly)
{
	t_env	*tmp;

	tmp = shelly->env;
	while (tmp != NULL)
	{
		if (tmp->type == 1)
		{
			printf("declare -x %s=\"%s\"\n", tmp->content, tmp->value);
		}
		else if (tmp->type == 0)
		{
			printf("declare -x %s\n", tmp->content);
		}
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

void	ft_export(t_shelly *shelly, char **av)
{
	int	i;

	i = 1;
	if (!av[1])
		affiche_export(shelly);
	while (av[i])
	{
		if (av[i][0] != '-' && ft_strcmp(av[i], "+=") != 0)
			add_or_not(shelly, av[i]);
		else
			printf("bash: export: `%s': not a valid identifier\n", av[i]);
		i++;
	}
}

// int main(int ac, char **av, char **envp) {

//  	t_shelly shelly;

//     (void)ac;
//     (void)av;

//     create_env_list(&shelly, envp);
// 	// add_or_not(&shelly,av[2]);
// 	// affiche_export(&shelly);
// 	if(if_export(av[1]) == 1)
// 	{
// 		ft_export(&shelly, av);
// 	}
// }

// int main(int ac, char **av, char **envp) {

//  t_shelly shelly;

//     (void)ac;
//     (void)av;

//     // Initialize the environment list
//     create_env_list(&shelly, envp);

//     // Check if the command is 'export'
//     if (if_export(av[0]) == 1)
//         ft_export(shelly.env);

//     return (0);
// }