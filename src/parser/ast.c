/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:57:56 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/12 15:04:48 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_command_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token && is_cmd(token->type) == 0)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**extract_command(t_token *token)
{
	int		count;
	char	**cmd;
	int		i;

	count = count_command_tokens(token);
	cmd = (char **)malloc((count + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && is_cmd(token->type) == 0)
	{
		cmd[i++] = strdup(token->str);
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_ast *create_ast_node(char **value, int node_type)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = value;
	node->node_type = node_type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*buid_left_pipe(t_token *tokens)
{
	t_token	*current;
	t_ast	*root;
	t_ast	*new_node;

	root = NULL;
	new_node = NULL;
	current = tokens;
	while (current && current->type != PIPE && current->type != HEREDOC)
	{
		if (is_cmd(current->type) == 1 && current->type != PIPE)
		{
			new_node = create_ast_node(NULL, current->type);
			new_node->left = root;
			current = current->next;
			new_node->right = buid_left_pipe(current);
			return (new_node);
		}
		else
		{
			root = create_ast_node(extract_command(current), CMD);
			while (current && is_cmd(current->type) == 0)
				current = current->next;
		}
	}
	return (root);
}

t_ast	*buid_left_heredoc(t_token *tokens)
{
	t_token	*current;
	t_ast	*root;
	t_ast	*new_node;

	root = NULL;
	new_node = NULL;
	current = tokens;
	while (current && current->type != HEREDOC)
	{
		if (is_cmd(current->type) == 1 && current->type != HEREDOC)
		{
			new_node = create_ast_node(NULL, current->type);
			new_node->left = root;
			current = current->next;
			new_node->right = buid_left_heredoc(current);
			return (new_node);
		}
		else
		{
			root = create_ast_node(extract_command(current), CMD);
			while (current && is_cmd(current->type) == 0)
				current = current->next;
		}
	}
	return (root);
}

t_ast	*create_ast(t_token *tokens)
{
	t_token	*current;
	t_ast	*root;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current && current->type != HEREDOC)
		current = current->next;
	if (current && current->type == HEREDOC)
	{
		root = create_ast_node(NULL, HEREDOC);
		root->left = buid_left_heredoc(tokens);
		root->right = create_ast(current->next);
		return (root);
	}
	current = tokens;
	root = NULL;
	while (current && current->type != PIPE)
		current = current->next;
	if (current && current->type == PIPE)
	{
		root = create_ast_node(NULL, PIPE);
		root->left = buid_left_pipe(tokens);
		root->right = create_ast(current->next);
		return (root);
	}
	current = tokens;
	while (current && (is_cmd(current->type) == 0 || current->type == PIPE
		|| current->type == HEREDOC))
		current = current->next;
	if (current && is_cmd(current->type) == 1 && current->type != PIPE
			&& current->type != HEREDOC)
		return (buid_left_pipe(tokens));
	current = tokens;
	if (is_cmd(current->type) == 0)
	{
		root = create_ast_node(extract_command(current), CMD);
		while (current && is_cmd(current->type) == 0)
			current = current->next;
	}
	return (root);
}
