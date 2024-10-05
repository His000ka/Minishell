/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:04 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/06 00:16:48 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check if the command is 'unset'
int if_unset(char *str)
{
	if (str && ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int is_valid_identifier(char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	int i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void remove_env_node(t_env **env_list, char *key)
{
	t_env *current = *env_list;
	t_env *previous = NULL;

	while (current != NULL)
	{
		if (ft_strcmp(current->content, key) == 0)
		{
			if (previous == NULL)
				*env_list = current->next;
			else
				previous->next = current->next;
			return;
		}
		previous = current;
		current = current->next;
	}
}

void ft_unset(t_env **env_list, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		// printf("STRING %s\n", args[i]);
		if (is_valid_identifier(args[i]))
			remove_env_node(env_list, args[i]);
		else
			printf("bash: unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
}

// int main(int ac, char **av, char **envp)
// {
//     t_shelly shelly;
//     create_env_list(&shelly, envp);  // Assuming create_env_list populates shelly's env_list

//     if (if_unset(av[1]) == 1)
//         ft_unset(&shelly.env_list, av);  // Access the environment list from shelly

//     return 0;
// }
