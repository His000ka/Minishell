/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:24:30 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/07 18:50:03 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_env(char *str)
{
	if (ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

void	ft_env(t_env *env_list)
{
	if (env_list == NULL)
	{
		printf("Error: Environment list is empty or null\n");
		return ;
	}
	while (env_list != NULL)
	{
		if (env_list->type == 1)
			printf("%s=%s\n", env_list->content, env_list->value);
		env_list = env_list->next;
	}
}

// int main(int ac, char **av, char **envp) {

// t_env	*env_list;

// 	(void)ac;
// 	(void)av;
// 	env_list = NULL;
// 	env_list = create_env_list(&env_list, envp);

// 	//print_env_list(env_list);

// 	if(if_env(av) == 1)
// 		ft_env(env_list);
//     return (0);
// }