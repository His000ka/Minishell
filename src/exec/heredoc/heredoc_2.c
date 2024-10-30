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
		if (current->right->left->node_type == PIPE)
			delimiter = ft_strdup(node->right->left->left->value[0]);
		else
		{
			while (current->right && current->right->left->node_type != CMD)
				current = current->right;
			delimiter = ft_strdup(node->right->left->value[0]);
		}
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

t_ast	*search_node_exec_heredoc(t_ast *node)
{
	t_ast	*tmp;
	char	**cmd;
	int		size;

	tmp = node;
	size = size_cmd_exec_heredoc(tmp);
	if (size == 0)
		return (NULL);
	cmd = adapt_cmd_exec_heredoc(tmp, size);
	if (!cmd)
		return (NULL);
	return (create_node_heredoc(CMD, cmd));
}

void	exec_fork_heredoc_3(t_shelly *shelly, t_ast *node, t_ast *node_exec)
{
	pid_t	pid;

	shelly->fd_in = shelly->fd[0];
	pid = fork();
	if (pid == 0)
	{
		if (dup2(shelly->fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(shelly->fd_in);
		if (node->right->node_type == TRUNC)
			return (exec_trunc_2(shelly, node->right, node_exec));
		else if (node->right->node_type == APPEND)
			return (exec_append_v2(shelly, node->right, node_exec));
		else
			ft_exec(shelly, node_exec);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(shelly->fd_in);
		waitpid(pid, NULL, 0);
	}
	else
		write(STDERR_FILENO, "ERROR FORK\n", 11);
}

int	adapt_cmd_2(t_shelly *shelly)
{
	t_token	*current;

	current = shelly->token;
	current = current->next;
	if (current->str)
		free(current->str);
	while (current->next && current->next->type != HEREDOC)
		current = current->next;
	shelly->token = current->next;
	ft_free_heredock(shelly, NULL, current);
	if (ft_parser(shelly) == 0)
	{
		if (exec_heredoc(shelly, shelly->ast) == 0)
			ft_exec(shelly, shelly->ast);
	}
	return (0);
}
