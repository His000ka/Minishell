/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:06:58 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/30 16:09:51 by pitroin          ###   ########.fr       */
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
		return (free(node), NULL);
	i = -1;
	while (copy[++i])
		node->value[i] = ft_strdup(copy[i]);
	node->value[i] = NULL;
	node->node_type = node_type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	count_values(char **values)
{
	int	count;

	count = 0;
	while (values[count])
		count++;
	return (count);
}

int	size_cmd_exec(t_ast *node)
{
	int	size;

	size = 0;
	if (node->left && node->left->node_type == CMD)
		size += count_values(node->left->value);
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		size += count_values(&node->left->value[1]);
	}
	if (node->right && node->right->node_type == CMD)
		size += count_values(&node->right->value[1]);
	else if (node->right && node->right->left)
		size += count_values(&node->right->left->value[1]);
	return (size);
}

char	**adapt_cmd_exec(t_ast *node, int size)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	if (node->left && node->left->node_type == CMD)
		cmd = fill_cmd_cmd(node->left, cmd, &i);
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		cmd = fill_cmd(node->left, cmd, &i);
	}
	if (node->right->node_type == CMD)
		cmd = fill_cmd(node->right, cmd, &i);
	else
		cmd = fill_cmd(node->right->left, cmd, &i);
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
	if (!cmd)
		return (NULL);
	return (create_node_exec(CMD, cmd));
}
