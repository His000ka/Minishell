/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:36:59 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 18:35:58 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_value(t_ast *node)
{
	t_ast	*tmp;

	tmp = node->right;
	if (!tmp->value)
		return (tmp->left->value[0]);
	return (tmp->value[0]);
}

void	exec_append(t_shelly *shelly, t_ast *node)
{
	int		fd_out;
	pid_t	pid;

	if (node->right->node_type != CMD)
        ft_exec(shelly, node->right);
	fd_out = open(search_value(node), O_WRONLY | O_CREAT | O_APPEND, 0644);
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
		ft_exec(shelly, node->left);
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

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
    int     fd_out;
    pid_t   pid;

    if (node->right->node_type != CMD)
        ft_exec(shelly, node->right);
    fd_out = open(search_value(node), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("ERROR OPEN");
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
        ft_exec(shelly, node->left);
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

void	exec_input(t_shelly *shelly, t_ast *node)
{
	int		fd_in;
	pid_t	pid;

	if (node->right->node_type == APPEND)
		return ;
	if (node->right->node_type != CMD)
        ft_exec(shelly, node->right);
	fd_in = open(search_value(node), O_RDONLY);
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
		ft_exec(shelly, node->left);
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

void	exec_cmd(t_shelly *shelly, t_ast *node)
{
	if (ft_builtins(shelly, node->value[0], node) == 0)
		return ;
	msg_cmd_not_found(node);
}

void	*ft_exec(t_shelly *shelly, t_ast *node)
{
	if (node->node_type == CMD)
		exec_cmd(shelly, node);
	else if (node->node_type == APPEND)
		exec_append(shelly, node);
	else if (node->node_type == TRUNC)
		exec_trunc(shelly, node);
	else if (node->node_type == INPUT)
		exec_input(shelly, node);
	return (NULL);
}
