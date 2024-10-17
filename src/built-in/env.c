/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:24:30 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/17 00:01:29 by firdawssema      ###   ########.fr       */
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
	t_env	*tmp;

	if (env_list == NULL)
	{
		printf("Error: Environment list is empty or null\n");
		return ;
	}
	tmp = env_list;
	while (tmp != NULL)
	{
		if (tmp->type == 1 && tmp->value != NULL && tmp->value[0] != '\0')
		{
			printf("%s=%s\n", tmp->content, tmp->value);
		}
		tmp = tmp->next;
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