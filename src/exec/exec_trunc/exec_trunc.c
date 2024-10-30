/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:58:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/18 17:45:22 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*mult_trunc(t_shelly *shelly, t_ast *node, t_ast *node_in)
{
	t_ast	*current;

	current = node;
	while (current->right && (current->right->node_type == TRUNC
			|| current->right->node_type == APPEND))
	{
		if (current->right->node_type == TRUNC)
			shelly->fd_out = open(search_value(current), O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else
			shelly->fd_out = open(search_value(current), O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		if (shelly->fd_out == -1)
			return (msg_permission(shelly, search_value(node)), NULL);
		close(shelly->fd_out);
		current = current->right;
	}
	if (current->node_type == APPEND)
	{
		exec_append_v2(shelly, current, node_in);
		return (NULL);
	}
	return (current);
}

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	t_ast	*current;

	current = mult_trunc(shelly, node, node->left);
	if (!current)
		return ;
	shelly->fd_out = open(search_value(current), O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (shelly->fd_out == -1)
		return (msg_permission(shelly, search_value(node)));
	pid = fork();
	if (pid == 0)
	{
		if (dup2(shelly->fd_out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(shelly->fd_out);
		if (node->left)
			ft_exec(shelly, node->left);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, shelly->fd_out, pid);
	else
		exit(EXIT_FAILURE);
	close(shelly->fd_out);
}

void	exec_trunc_2(t_shelly *shelly, t_ast *node, t_ast *node_in)
{
	pid_t	pid;
	t_ast	*current;

	current = mult_trunc(shelly, node, node_in);
	if (!current)
		return ;
	shelly->fd_out = open(search_value(current), O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (shelly->fd_out == -1)
		return (msg_permission(shelly, search_value(node)));
	pid = fork();
	if (pid == 0)
	{
		if (dup2(shelly->fd_out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(shelly->fd_out);
		if (node_in)
			ft_exec(shelly, node_in);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, shelly->fd_out, pid);
	else
		exit(EXIT_FAILURE);
	close(shelly->fd_out);
}
