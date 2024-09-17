/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shelly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:25 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:51:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int init_env(char **envp, t_env **env)
{
    int i;

    i = 0;
    while (envp[i])
		i++;
    *env = NULL;
    for (int j = 0; j < i; j++)
    {
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node)
            return 1;  // Erreur d'allocation

        char *equal_sign = strchr(envp[j], '=');
        if (equal_sign)
        {
            new_node->content = strndup(envp[j], equal_sign - envp[j]);
            new_node->value = strdup(equal_sign + 1);
        }
        else
        {
            new_node->content = strdup(envp[j]);
            new_node->value = NULL;
        }
        if (!new_node->content || (equal_sign && !new_node->value))
        {
            free(new_node->content);
            free(new_node->value);
            free(new_node);
            return 1;
        }
        new_node->next = *env;
        *env = new_node;
    }
    return 0;
}

int init_shelly(t_shelly *shelly)
{
    int check;

    check = 0;
    // shelly->env = NULL;
    // check += init_env(envp, &(shelly->env));
    // if (check > 0)
    //     return ft_error("ERROR INIT\n", 0, 0);

    shelly->str = NULL;
    shelly->token = NULL;
    shelly->cmd = NULL;
    shelly->ast = NULL;
    // shelly->env = NULL;
    return check;
}
