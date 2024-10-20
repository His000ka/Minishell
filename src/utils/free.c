/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/05 11:48:27 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 11:49:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_command(char **cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i] != NULL)
			free(cmd[i++]);
		free(cmd);
		cmd = NULL;
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->value)
		free_command(node->value);
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	free(node);
	node = NULL;
}

void	free_env(t_shelly *shelly)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (shelly->envp)
	{
		while (shelly->envp[i] != NULL)
			free(shelly->envp[i++]);
		free(shelly->envp);
	}
	while (shelly->env)
	{
		tmp = shelly->env;
		shelly->env = shelly->env->next;
		free(tmp->value);
		free(tmp->content);
		free(tmp);
	}
	if (shelly->envp)
		free(shelly->envp);
	shelly->env = NULL;
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

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
	if (shelly->cmd != NULL)
	{
		free(shelly->cmd);
		shelly->cmd = NULL;
	}
}
