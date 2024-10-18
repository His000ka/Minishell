/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:58:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/18 12:03:03 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
	int		fd_out;
	pid_t	pid;
	t_ast	*current;
	int		status;

	current = node;
	while (current->right && current->right->node_type == TRUNC)
	{
		fd_out = open(search_value(current), O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (fd_out == -1)
			return ;
		close(fd_out);
		current = current->right;
	}
	fd_out = open(search_value(current), O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		if (node->left)
			ft_exec(shelly, node->left);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_out);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			int exit_code = WEXITSTATUS(status);
			shelly->exit_code = exit_code;
			printf("status %d\n", shelly->exit_code);
		}
		else
			shelly->exit_code = 1;
    }
	else
		exit(EXIT_FAILURE);
}

