/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:57:41 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/26 17:26:44 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <errno.h>

t_ast	*search_file(t_shelly *shelly, t_ast *node)
{
	if (node->right->node_type == CMD)
	{
		if (shelly->fd_in != -1)
			close(shelly->fd_in);
		shelly->fd_in = open(search_value(node), O_RDONLY);
		if (shelly->fd_in == -1)
			return (msg_permission(shelly, search_value(node)), NULL);
		return (node);
	}
	while (node->right && node->node_type == INPUT)
	{
		if (shelly->fd_in != -1)
			close(shelly->fd_in);
		shelly->fd_in = open(search_value(node), O_RDONLY);
		if (shelly->fd_in == -1)
			return (msg_not_file(shelly, search_value(node)), NULL);
		node = node->right;
	}
	return (node);
}

void	child_input(t_shelly *shelly, t_ast *node_current, t_ast *node_exec)
{
	if (dup2(shelly->fd_in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(shelly->fd_out);
	if (node_current->node_type == TRUNC)
		exec_trunc_2(shelly, node_current, node_exec);
	else if (node_current->node_type == APPEND)
		exec_append_v2(shelly, node_current, node_exec);
	else
		ft_exec(shelly, node_exec);
}

void	exec_input(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	t_ast	*node_current;
	t_ast	*node_exec;

	node_current = search_file(shelly, node);
	node_exec = search_node_exec(node);
	if (!node_exec || !node_current)
		return ;
	pid = fork();
	if (pid == 0)
	{
		child_input(shelly, node_current, node_exec);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, shelly->fd_in, pid);
	else
		exit(EXIT_FAILURE);
	free_ast(node_exec);
}
