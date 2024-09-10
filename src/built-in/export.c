/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 10:41:19 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char **str)
{
	if (ft_strncmp(str[1], "export", 6) == 0)
		return (1);
	return (0);
}

void	ft_export(t_env *list_env)
{
	   while (list_env != NULL) {
        printf("declare -x %s=\"%s\"\n", list_env->content, list_env->value);
        list_env = list_env->next;
    }
}

int main(int ac, char **av, char **envp) {

t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = NULL;
	env_list = create_env_list(&env_list, envp);

	//print_env_list(env_list);

	if(if_export(av) == 1)
		ft_export(env_list);
    return 0;
}