/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:36:59 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 09:36:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_append(t_ast *node)
{
	int		fd_out;
	pid_t	pid;

	fd_out = open(node->right->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		write(STDERR_FILENO, "ERROR OPEN\n", 11);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			write(STDERR_FILENO, "ERROR DUP2\n", 11);
			exit(EXIT_FAILURE);
		}
		close(fd_out);
		ft_exec(node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_out);
		waitpid(pid, NULL, 0);
	}
	else
	{
		write(STDERR_FILENO, "ERROR FORK\n", 11);
		exit(EXIT_FAILURE);
	}
}


void	exec_trunc(t_ast *node)
{
	int		fd_out;
	pid_t	pid;

	if (node->right->node_type != CMD)
		ft_exec(node->right);
	fd_out = open(node->right->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_error("ERROR OPEN\n", 0, 0);
		return ;
	}

	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("ERROR DUP2");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
		ft_exec(node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_out);
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("ERROR FORK");
		exit(EXIT_FAILURE);
	}
}

void	exec_input(t_ast *node)
{
	int		fd_in;
	pid_t	pid;

	fd_in = open(node->right->value[0], O_RDONLY);
	if (fd_in == -1)
	{
		msg_not_file(node->right);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			write(STDERR_FILENO, "ERROR DUP2\n", 11);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
		ft_exec(node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_in);
		waitpid(pid, NULL, 0);
	}
	else
	{
		write(STDERR_FILENO, "ERROR FORK\n", 11);
		exit(EXIT_FAILURE);
	}
}

void	exec_cmd(t_ast *node)
{
	msg_cmd_not_found(node);
}

int	ft_exec(t_ast *node)
{
	if (node->node_type == CMD)
		exec_cmd(node);
	else if (node->node_type == APPEND)
		exec_append(node);
	else if (node->node_type == TRUNC)
		exec_trunc(node);
	else if (node->node_type == INPUT)
		exec_input(node);
	return (0);
}