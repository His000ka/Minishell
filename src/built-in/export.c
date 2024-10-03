/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/02 20:44:38 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char *str)
{
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	return (0);
}


// Helper function to count the number of environment variables
int	env_count(t_env *list_env)
{
    int count = 0;
    while (list_env)
    {
        count++;
        list_env = list_env->next;
    }
    return (count);
}

// Custom bubble sort using while loops
void sort_env_array(t_env **env_array, int count)
{
    int i = 0;
    int j;
    t_env *temp;
    int swapped;

    // Sorting with a while loop
    while (i < count - 1)
    {
        j = 0;
        swapped = 0; // To track if any swap happened

        while (j < count - i - 1)
        {
            if (ft_strncmp(env_array[j]->content, env_array[j + 1]->content, ft_strlen(env_array[j]->content) + 1) > 0)
            {
                temp = env_array[j];
                env_array[j] = env_array[j + 1];
                env_array[j + 1] = temp;
                swapped = 1;
            }
            j++;
        }

        if (swapped == 0) // If no swap happened, array is already sorted
            break;

        i++;
    }
}

// Function to export environment variables in sorted order
void	ft_export(t_env *list_env)
{
    int     count = env_count(list_env);
    t_env   **env_array;
    int     i = 0;

    // Allocate an array to store pointers to environment variables
    env_array = (t_env **)malloc(sizeof(t_env *) * count);
    if (!env_array)
        return ;

    // Fill the array with pointers to environment variables
    while (list_env)
    {
        env_array[i++] = list_env;
        list_env = list_env->next;
    }

    // Sort the environment variables using bubble sort with while loops
    sort_env_array(env_array, count);

    // Print the sorted environment variables
    i = 0;
    while (i < count)
    {
        if (env_array[i]->value != NULL)
        {
            if (env_array[i]->value[0] == '\0')
                printf("declare -x %s=\"\"\n", env_array[i]->content);  // Empty string case
            else
                printf("declare -x %s=\"%s\"\n", env_array[i]->content, env_array[i]->value);  // Variable with value
        }
        else
        {
            printf("declare -x %s\n", env_array[i]->content);  // Variable without value
        }
        i++;
    }

    // Free the allocated memory
    free(env_array);
}


// int main(int ac, char **av, char **envp) {

//  t_shelly shelly;

//     (void)ac;
//     (void)av;

//     // Initialize the environment list
//     create_env_list(&shelly, envp);

//     // Check if the command is 'export'
//     if (if_export(av[0]) == 1)
//         ft_export(shelly.env);

//     return 0;
// }