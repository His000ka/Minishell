/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/09 19:12:16 by fimazouz         ###   ########.fr       */
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
		printf("declare -x %s=\"%s\"\n", tmp->content,
			tmp->value);
		tmp = tmp->next;
	}
}

void	add_or_not(t_shelly *shelly, char *str)
{
	t_env	*export_str;
	t_env	*prev;

	export_str = create_env_node(str);
	printf("La variable = %s, la valeur : %s", export_str->content,export_str->value);
	prev = shelly->env;
	while (shelly->env != NULL)
	{
		// printf("jss la");
		
		if (ft_strcmp(export_str->content, shelly->env->content) == 0)
		{
			//printf("je suis la");
			if (export_str->value != NULL)
			{
				if (ft_strcmp(export_str->value, shelly->env->value) != 0)
				{
					free(shelly->env->value);
					shelly->env->value = ft_strdup(export_str->value);
					break ;
				}
			}
		}
		shelly->env = shelly->env->next;
	}
	if (shelly->env == NULL)
	{
		// printf("CAMKNDJKSA0");
		shelly->env = prev;
		add_node_env(&shelly->env, export_str);
	}
}

void	ft_export(t_shelly *shelly, char **av)
{
	int	i;
	
	i = 1;
	if (!av[1])
		affiche_export(shelly);
	while (av[i])
	{
		if (av[i][0] != '-')
			add_or_not(shelly, av[i]);
		else
			printf("bash: export: `%s': not a valid identifier", av[i]);
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