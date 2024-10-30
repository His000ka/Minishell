/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:26:50 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/30 16:58:51 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*create_node_heredoc(int node_type, char **copy)
{
	t_ast	*node;
	int		size;
	int		i;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	size = 0;
	while (copy && copy[size])
		size++;
	node->value = malloc(sizeof(char *) * (size + 1));
	if (!node->value)
		return (NULL);
	i = -1;
	while (copy[++i])
		node->value[i] = ft_strdup(copy[i]);
	node->value[i] = NULL;
	node->node_type = node_type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	count_values_heredoc(char **values)
{
	int	count;

	count = 0;
	if (!values)
		return (0);
	while (values[count])
		count++;
	return (count);
}

int	size_node_left(t_ast *node)
{
	int	size;

	size = 0;
	if (node->left && node->left->node_type == CMD)
		size += count_values_heredoc(node->left->value);
	else if (node->left)
	{
		while (node->left && node->left->node_type != CMD)
		{
			if (node->left->right)
				size += count_values_heredoc(node->left->right->value);
			node = node->left;
		}
		if (node->left && node->left->node_type == CMD)
			size += count_values_heredoc(node->left->value);
	}
	return (size);
}

int	size_cmd_exec_heredoc(t_ast *node)
{
	int		size;

	size = 0;
	if (node->left)
		size += size_node_left(node);
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		if (node->left->value && node->left->value[1])
			size += count_values_heredoc(&node->left->value[1]);
	}
	if (node->right && node->right->node_type == CMD)
		size += count_values_heredoc(&node->right->value[1]);
	else if (node->right && node->right->left)
	{
		if (node->right->left->value && node->right->left->value[1])
			size += count_values_heredoc(&node->right->left->value[1]);
	}
	return (size);
}
