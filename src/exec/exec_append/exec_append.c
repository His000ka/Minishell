/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:09:37 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/18 14:03:35 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exec_append(t_shelly *shelly, t_ast *node)
{
	int		fd_out;
	pid_t	pid;

	if (node->right->node_type != CMD)
		ft_exec(shelly, node->right);
	fd_out = open(search_value(node), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			write(STDERR_FILENO, "ERROR DUP2\n", 11);
			exit(EXIT_FAILURE);
		}
		close(fd_out);
		if (node->left)
			ft_exec(shelly, node->left);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, fd_out, pid);
	else
		exit(EXIT_FAILURE);
}
