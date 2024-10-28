/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:57:41 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/19 18:05:31 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	transform_value_2(t_ast *node)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(node->value[0]);
	tmp2 = ft_strdup(node->value[1]);
	free(node->value[0]);
	free(node->value[1]);
	node->value[0] = ft_strdup(tmp2);
	node->value[1] = ft_strdup(tmp);
	free(tmp);
	free(tmp2);
}

void	transform_value(t_ast *node)
{
	char	*tmp;
	int		i;

	if (!node->value[1])
		return ;
	else if (!node->value[2])
		transform_value_2(node);
	else
	{
		i = 0;
		free(node->value[0]);
		while (node->value[++i])
		{
			tmp = ft_strdup(node->value[i]);
			free(node->value[i]);
			node->value[i] = NULL;
			node->value[i - 1] = ft_strdup(tmp);
			free(tmp);
		}
	}
}

void	input_form_special(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(shelly->fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (node->right->node_type == CMD)
		{
			transform_value(node->right);
			ft_exec(shelly, node->right);
		}
		else if (node->right->node_type == TRUNC)
		{
			transform_value(node->right->left);
			exec_trunc_2(shelly, node->right, node->right->left);
		}
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, shelly->fd_in, pid);
	else
		exit(EXIT_FAILURE);
}

t_ast	*search_file(t_shelly *shelly, t_ast *node)
{
	if (node->right->node_type == CMD)
	{
		if (shelly->fd_in == -1)
			close(shelly->fd_in);
		shelly->fd_in = open(search_value(node), O_RDONLY);
		if (shelly->fd_in == -1)
			return (msg_not_file(shelly, search_value(node)), NULL);
		return (node);
	}
	while (node->right && node->node_type == INPUT)
	{
		if (shelly->fd_in == -1)
			close(shelly->fd_in);
		shelly->fd_in = open(search_value(node), O_RDONLY);
		if (shelly->fd_in == -1)
			return (msg_not_file(shelly, search_value(node)), NULL);
		node = node->right;
	}
	return (node);
}

t_ast	*create_node_exec(int node_type, char **copy, int i)
{
	t_ast	*node;
	int		size;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	size = 0;
	while (copy && copy[size])
		size++;
	node->value = malloc(sizeof(char *) * (size + i + 1));
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

char	**adapt_cmd_exec(t_ast *node, int i, char ***cmd)
{
	char	**tmp;
	int j;

	j = 0;
	while (*cmd && *cmd[j])
		j++;
	printf("i: %d et j: %d\n", i, j);
	tmp = malloc(sizeof(char *) * (j + i + 10));
	i = 0;
	while (*cmd && *cmd[i])
	{
		tmp[i] = ft_strdup(*cmd[i]);
		i++;
	}
	j = 1;
	while (node->value[j])
	{
		tmp[i++] = node->value[j];
		i++;
		j++;
	}
	tmp[i] = NULL;
	j = 0;
	while (*cmd && *cmd[j])
		free(*cmd[j]);
	if (*cmd)
		free(*cmd);
	return (tmp);
}

t_ast	*search_node_exec(t_ast *node)
{
	t_ast	*tmp;
	char	**cmd;
	int		i;

	tmp = node;
	cmd = NULL;
	if (tmp->left && tmp->left->node_type == CMD)
		return (tmp->left);
	while (tmp->right && tmp->right->node_type == INPUT)
	{
		tmp = node->right;
		i = 1;
		while (tmp->left->value[i])
			i++;
		if (i > 1)
			cmd = adapt_cmd_exec(node->left, i, &cmd);
	}
	if (tmp->right->node_type == CMD)
	{
		i = 1;
		while (tmp->right->value[i])
			i++;
		if (i > 1)
			cmd = adapt_cmd_exec(node->right, i, &cmd);
	}
	else
	{
		if (tmp->right->left->value[1])
		{
			free(tmp->right->left->value[0]);
			tmp->right->left->value[0] = ft_strdup(tmp->right->left->value[1]);
			free(tmp->right->left->value[1]);
			tmp->right->left->value[1] = NULL;
			return(tmp->right->left);
		}
	}
	return (create_node_exec(CMD, cmd, i));
}


void	exec_input(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	t_ast	*node_exec;
	t_ast	*node_current;

	if (node->right->node_type == APPEND)
		return ;
	node_current = search_file(shelly, node);
	if (node_current == NULL)
		return ;
	node_exec = search_node_exec(node);
	// node_exec_adapt = adapt_node_exec(node, node_exec);
	// if (!node->left && node->right->node_type != INPUT)
	// 	return (input_form_special(shelly, node));
	pid = fork();
	if (pid == 0)
	{
		if (dup2(shelly->fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		// printf("nodetype: %s\n", node->right-> );
		if (node_exec && node_current->node_type == TRUNC)
			exec_trunc_2(shelly, node_current, node_exec);
		else if (node_exec)
			ft_exec(shelly, node_exec);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, shelly->fd_in, pid);
	else
		exit(EXIT_FAILURE);
	// free_ast(node_current);
	free_ast(node_exec);
}
