/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:36:59 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 19:36:21 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_value(t_ast *node)
{
	t_ast	*tmp;

	tmp = node->right;
	if (!tmp->value)
		return (tmp->left->value[0]);
	return (tmp->value[0]);
}

char *get_env_value(t_env *env, const char *key)
{
    t_env *tmp = env;

    while (tmp)
    {
        if (ft_strncmp(tmp->value, key, ft_strlen(key)) == 0 && tmp->value[ft_strlen(key)] == '=')
            return (tmp->value + ft_strlen(key) + 1);
        tmp = tmp->next;
    }
    return (NULL);
}

void	exec_cmd(t_shelly *shelly, t_ast *node)
{
	if (shelly->exit_status)
			free(shelly->exit_status);
	shelly->exit_status = ft_strdup("0");
	if (ft_builtins(shelly, node->value[0], node) == 0)
	{
		shelly->exit_status = ft_strdup("0");
		return ;
	}
	if (exec_cmd_path(node->value[0], node->value, shelly->envp) == 0)
	{
		shelly->exit_status = ft_strdup("0");
		return ;
	}
	if (shelly->exit_status)
			free(shelly->exit_status);
	shelly->exit_status = ft_strdup("127");
	msg_cmd_not_found(node);
}

void	*ft_exec(t_shelly *shelly, t_ast *node)
{
	if (node->node_type == CMD)
		exec_cmd(shelly, node);
	else if (node->node_type == APPEND)
		exec_append(shelly, node);
	else if (node->node_type == TRUNC)
		exec_trunc(shelly, node);
	else if (node->node_type == INPUT)
		exec_input(shelly, node);
	else if(node->node_type == PIPE)
		exec_pipe(shelly, node);
	return (NULL);
}
