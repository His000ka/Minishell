/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapte_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:55:27 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/30 16:58:44 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	**handle_left_cmd(t_ast *node, char **cmd, int *i)
{
	t_ast	*tmp;

	tmp = node;
	while (tmp->left && tmp->left->node_type != CMD)
	{
		cmd = fill_cmd(tmp->left->right, cmd, i);
		tmp = node->left;
	}
	if (tmp->left && tmp->left->node_type == CMD)
		cmd = fill_cmd_cmd(tmp->left, cmd, i);
	return (cmd);
}

static char	**handle_right_cmd(t_ast *node, char **cmd, int *i)
{
	while (node->right && node->right->node_type == INPUT)
	{
		node = node->right;
		cmd = fill_cmd(node->left, cmd, i);
	}
	if (node->right->node_type == CMD)
		cmd = fill_cmd(node->right, cmd, i);
	else
		cmd = fill_cmd(node->right->left, cmd, i);
	return (cmd);
}

char	**adapt_cmd_exec_heredoc(t_ast *node, int size)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	if (node->left && node->left->node_type == CMD)
		cmd = fill_cmd_cmd(node->left, cmd, &i);
	else if (node->left)
		cmd = handle_left_cmd(node, cmd, &i);
	cmd = handle_right_cmd(node, cmd, &i);
	cmd[i] = NULL;
	return (cmd);
}
