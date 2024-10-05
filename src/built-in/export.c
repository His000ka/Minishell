/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/06 00:42:27 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char *str)
{
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	return (0);
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