/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:04 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/15 19:22:00 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check if the command is 'unset'
int if_unset(char *str)
{
	if (str && ft_strncmp(str, "unset", 5) == 0 && (str[5] == '\0' || str[5] == ' '))
		return (1);
	return (0);
}

// Function to remove a node from the environment list by its key
void remove_env_node(t_env **env_list, char *key)
{
	t_env *current = *env_list;
	t_env *previous = NULL;

	while (current != NULL)
	{
		// If the key matches, remove the node
		if (ft_strcmp(current->content, key) == 0)
		{
			// Unlink the node from the list
			if (previous == NULL)
				*env_list = current->next;  // Removing the head node
			else
				previous->next = current->next;

			// Free the memory associated with the node
			free(current->content);
			free(current->value);
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

// Function to handle the 'unset' command
int ft_unset(t_env **env_list, char **args)
{
	int i = 1;

	// Loop through all the arguments passed to 'unset'
	while (args[i])
	{
		// Check if the argument is a valid identifier
		if (is_valid_identifier(args[i]))
		{
			remove_env_node(env_list, args[i]);
		}
		else
		{
			printf("bash: unset: `%s': not a valid identifier\n", args[i]);
		}
		i++;
	}
	return (0);
}

// Uncomment the main for testing
int main(int ac, char **av, char **envp)
{
    t_env *env_list = NULL;
    env_list = create_env_list(&env_list, envp);

    if (if_unset(av[1]) == 1)
        ft_unset(&env_list, av);

    return 0;
}
