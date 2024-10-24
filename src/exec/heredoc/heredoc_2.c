/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:19 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:18 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*search_delimiter(t_ast *node)
{
	t_ast	*current;
	char	*delimiter;

	current = node;
	if (node->right->node_type == CMD)
		delimiter = ft_strdup(node->right->value[0]);
	else
	{
		while (current->right && current->right->left->node_type != CMD)
			current = current->right;
		delimiter = ft_strdup(node->right->left->value[0]);
	}
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

void	ft_free_heredock(t_shelly *shelly, t_token	*current, t_token	*tmp)
{
	if (current)
		free(current);
	if (tmp)
		free(tmp);
	free(shelly->ast);
}

void	not_cmd_left(t_shelly *shelly)
{
	if (shelly->token->next)
		shelly->token = shelly->token->next;
	else
		return ;
	if (shelly->token->next)
		shelly->token = shelly->token->next;
	else
		return ;
	if (shelly->token->type == PIPE && shelly->token->next)
		shelly->token = shelly->token->next;
	else
		return ;
	//affiche_token(shelly);
	free_ast(shelly->ast);
	if (ft_parser(shelly) == 0)
	{
		if (exec_heredoc(shelly, shelly->ast) == 0)
			ft_exec(shelly, shelly->ast);
	}
}

void	exec_fork_heredoc_v2(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	int		fd_in;

	fd_in = shelly->fd[0];
	pid = fork();
	recup_value_1(node);
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_in);
		if (node->value)
			ft_exec(shelly, node);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(fd_in);
		waitpid(pid, NULL, 0);
	}
	else
		write(STDERR_FILENO, "ERROR FORK\n", 11);
}

int	exec_heredoc_2(t_shelly *shelly, t_ast *node)
{
	if (pipe(shelly->fd) < 0)
		return (ft_error("pipe", 0, 0));
	read_heredoc(shelly);
	free(shelly->delimiter);
	close(shelly->fd[1]);
	if (node->right->node_type == CMD && !node->right->value[1])
		exec_fork_heredoc(shelly, node);
	else if (!node->left && node->right->node_type == CMD && node->right->value[1] && !node->right->value[2])
		exec_fork_heredoc_v2(shelly, node->right);
	else if (!node->left || node->right->right->node_type == PIPE)
		not_cmd_left(shelly);
	else
		adapt_cmd(shelly);
	return (0);
}

int	exec_heredoc(t_shelly *shelly, t_ast *node)
{
	if (node->node_type != HEREDOC)
		return (0);
	shelly->delimiter = search_delimiter(node);
	if (!shelly->delimiter)
		return (1);
	exec_heredoc_2(shelly, node);
	return (1);
}
