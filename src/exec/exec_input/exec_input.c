/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:57:41 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/18 12:11:53 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		shelly->exit_code = 1;
		return ;
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
		if (node->left)
			ft_exec(shelly, node->left);
		exit(shelly->exit_code);
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
