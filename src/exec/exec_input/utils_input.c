/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:06:58 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/28 15:12:23 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*create_node_exec(int node_type, char **copy)
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

int	size_cmd_exec(t_ast *node)
{
	int	size;
	int	i;

	size = 0;
	if (node->left && node->left->node_type == CMD)
	{
		while (node->left->value[size])
			size++;
	}
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		i = 1;
		while (node->left->value[i++])
			size++;
	}
	if (node->right->node_type == CMD)
	{
		i = 1;
		while (node->right->value[i++])
			size++;
	}
	else
	{
		i = 1;
		while (node->right->left->value[i++])
			size++;
	}
	return (size);
}

char	**adapt_cmd_exec(t_ast *node, int size)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	if (node->left && node->left->node_type == CMD)
	{
		while (node->left->value[i])
		{
			cmd[i] = ft_strdup(node->left->value[i]);
			i++;
		}
	}
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		j = 0;
		while (node->left->value[++j])
			cmd[i++] = ft_strdup(node->left->value[j]);
	}
	if (node->right->node_type == CMD)
	{
		j = 0;
		while (node->right->value[++j])
			cmd[i++] = ft_strdup(node->right->value[j]);
	}
	else
	{
		j = 0;
		while (node->right->left->value[++j])
			cmd[i++] = ft_strdup(node->right->left->value[j]);
	}
	cmd[i] = NULL;
	return (cmd);
}

t_ast	*search_node_exec(t_ast *node)
{
	t_ast	*tmp;
	char	**cmd;
	int		size;

	tmp = node;
	size = size_cmd_exec(tmp);
	if (size == 0)
		return (NULL);
	cmd = adapt_cmd_exec(tmp, size);
	if (cmd == NULL)
		return (NULL);
	return (create_node_exec(CMD, cmd));
}
