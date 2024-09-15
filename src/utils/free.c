/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:48:27 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:49:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_command(char **cmd)
{
	int	i;

	i = 0;
    if (cmd)
	{
        while (cmd[i] != NULL)
            free(cmd[i++]);
        free(cmd);
    }
}

// Fonction récursive pour libérer tout l'arbre AST
void	free_ast(t_ast *node)
{
    if (!node)
        return;
    if (node->left)
        free_ast(node->left);
    if (node->right)
        free_ast(node->right);
    if (node->value)
        free_command(node->value);
    free(node);
}

// void	free_envp(t_env *env)
// {
// 	int	i;

// 	i = -1;
// 	while (env->envp[++i] != NULL)
// 		free(env->envp[i]);
// 	free(env->envp);
// }

void free_tokens(t_token *token)
{
	t_token *tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}


void	ft_free(t_shelly *shelly)
{
	int	i;

	if (shelly->str != NULL)
	{
		i = 0;
		while (shelly->str[i])
			free(shelly->str[i++]);
		free(shelly->str);
		shelly->str = NULL;
	}
	if (shelly->token != NULL)
	{
		free_tokens(shelly->token);
		shelly->token = NULL;
	}
	// if (shelly->env != NULL)
	// {
	// 	if (shelly->env->envp != NULL)
	// 		free_envp(shelly->env);
	// 	free(shelly->env);
	// 	shelly->env = NULL;
	// }
	if (shelly->cmd != NULL)
	{
		free(shelly->cmd);
		shelly->cmd = NULL;
	}
}