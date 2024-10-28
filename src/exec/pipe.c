/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:38:01 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/22 12:11:19 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	after_pipe(t_shelly *shelly)
{
	char	*input;
	char	*tmp;

	input = readline("Pipe>");
	if (input)
	{
		tmp = ft_strjoin(shelly->cmd, input);
		if (!tmp)
			return ;
		free_ast(shelly->ast);
		ft_free(shelly);
		shelly->cmd = ft_strdup(tmp);
		if (!shelly->cmd)
			return ;
		if (ft_lexer(shelly) == 0)
		{
			if (ft_parser(shelly) == 0)
			{
				if (exec_heredoc(shelly, shelly->ast) == 0)
					ft_exec(shelly, shelly->ast);
			}
		}
	}
}

void	child_process_left(t_shelly *shelly, t_ast *node, int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_exec(shelly, node->left);
	exit(shelly->exit_code);
}

void	child_process_right(t_shelly *shelly, t_ast *node, int pipe_fd[2])
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_exec(shelly, node->right);
	exit(shelly->exit_code);
}

void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	exec_pipe(t_shelly *shelly, t_ast *node)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node->right)
		return (after_pipe(shelly));
	if (pipe(pipe_fd) == -1)
		perror("Pipe error");
	pid1 = fork();
	if (pid1 == -1)
		perror("Fork error (left process)");
	if (pid1 == 0)
		child_process_left(shelly, node, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		perror("Fork error (right process)");
	if (pid2 == 0)
		child_process_right(shelly, node, pipe_fd);
	close_pipes(pipe_fd);
	status_pipe(pid1, pid2, shelly);
}
