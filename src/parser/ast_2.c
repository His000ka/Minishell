/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:18 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/07 11:41:59 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_ast	*ast_heredoc(t_token *tokens, t_ast *root)
{
	t_token	*current;

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
	return (NULL);
}

t_ast	*ast_pipe(t_token *tokens, t_ast *root)
{
	t_token	*current;

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
	return (NULL);
}

t_ast	*ast_priority(t_token *tokens, t_ast *root)
{
	root = NULL;
	root = ast_heredoc(tokens, root);
	if (root)
		return (root);
	root = ast_pipe(tokens, root);
	if (root)
		return (root);
	return (NULL);
}
