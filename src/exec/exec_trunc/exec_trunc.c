/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:58:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/25 18:49:28 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*mult_trunc(t_ast *node)
{
	t_ast	*current;
	int		fd_out;

	current = node;
	while (current->right && current->right->node_type == TRUNC)
	{
		fd_out = open(search_value(current), O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (fd_out == -1)
			return (NULL);
		close(fd_out);
		current = current->right;
	}
	return (current);
}

void	exec_trunc(t_shelly *shelly, t_ast *node)
{
	int		fd_out;
	pid_t	pid;
	t_ast	*current;

	current = mult_trunc(node);
	if (!current)
		return ;
	fd_out = open(search_value(current), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
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
