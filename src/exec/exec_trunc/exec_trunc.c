/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:58:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/08 12:57:34 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	trunc_right(t_ast *node)
{
	t_ast	*current;
	int		fd_out;

	current = node;
	while (current->right && current->right->node_type == TRUNC)
	{
		fd_out = open(search_value(current),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			return (-1);
		close (fd_out);
		current = current->right;
	}
	fd_out = open(search_value(current),
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd_out);
}

int	trunc_input(t_shelly *shelly, t_ast *node)
{
	t_ast *current;

	current = node;
	while (current->right && current->right->node_type == TRUNC)
		current = current->right;
	if (current->right->node_type == INPUT)
	{
		ft_exec(shelly, node->right);
		return (1);
	}
	return (0);
}

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
	int		fd_out;
	pid_t	pid;

	fd_out = trunc_right(node);
	if (fd_out == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_out);
		if (node->left && trunc_input(shelly, node) == 0)
			ft_exec(shelly, node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_out);
		waitpid(pid, NULL, 0);
	}
	else
		exit(EXIT_FAILURE);
}
