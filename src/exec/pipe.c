/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:38:01 by firdawssema       #+#    #+#             */
/*   Updated: 2024/10/08 19:56:08 by fimazouz         ###   ########.fr       */
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

void	exec_pipe(t_shelly *shelly, t_ast *node)
{
	int	pipe_fd[2];

	pid_t pid1, pid2;
	if (!node->right)
		return (after_pipe(shelly));
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (node->left)
			ft_exec(shelly, node->left);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		if (node->right)
			ft_exec(shelly, node->right);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
