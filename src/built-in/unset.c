/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:04 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/02 20:56:44 by firdawssema      ###   ########.fr       */
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

// Helper function to check if a string is a valid identifier
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

// Function to remove a node from the environment list by its key
void remove_env_node(t_env **env_list, char *key)
{
	t_env *current = *env_list;
	t_env *previous = NULL;

	while (current != NULL)
	{
		// If the key matches, remove the node
		if (ft_strncmp(current->content, key, ft_strlen(key) + 1) == 0)
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
void ft_unset(t_env **env_list, char **args)
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
}

// int main(int ac, char **av, char **envp)
// {
//     t_shelly shelly;
//     create_env_list(&shelly, envp);  // Assuming create_env_list populates shelly's env_list

//     if (if_unset(av[1]) == 1)
//         ft_unset(&shelly.env_list, av);  // Access the environment list from shelly

//     return 0;
// }
