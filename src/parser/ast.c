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
		cmd[i++] = ft_strdup(token->str);
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_ast	*create_ast_node(char **value, int node_type)
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

t_ast	*create_ast(t_token *tokens)
{
	t_token	*current;
	t_ast	*root;

	if (!tokens)
		return (NULL);
	root = NULL;
	root = ast_priority(tokens, root);
	if (root)
		return (root);
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
