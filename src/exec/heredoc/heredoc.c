/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:52 by marvin            #+#    #+#             */
/*   Updated: 2024/10/18 14:31:12 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_heredoc(t_shelly *shelly, t_ast *node)
{
	if (node->node_type == CMD)
		return (0);
	if (node->node_type == PIPE || node->node_type == TRUNC
		|| node->node_type == APPEND || node->node_type == INPUT)
		return (search_heredoc(shelly, node->right) || search_heredoc(shelly,
				node->left));
	if (node->node_type == HEREDOC)
		return (exec_heredoc(shelly, node));
	return (0);
}

char	*search_delimiter(t_ast *node)
{
	t_ast	*current;
	char	*delimiter;

	current = node;
	if (node->right->node_type == CMD)
	{
		delimiter = ft_strdup(node->right->value[0]);
	}	
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

void	read_heredoc(t_shelly *shelly)
{
	char	*input;

	while (1)
	{
		input = readline("Heredoc>");
		if (ft_strcmp(input, shelly->delimiter) == 0)
		{
			free(input);
			break ;
		}
		if (input)
		{
			write(shelly->fd[1], input, ft_strlen(input));
			write(shelly->fd[1], "\n", 1);
		}
		free(input);
	}
}

int	adapt_cmd(t_shelly *shelly)
{
	t_token	*current;
	t_token	*tmp;

	current = shelly->token;
	while (current && current->type != HEREDOC)
		current = current->next;
	if (!current)
		return (0);
	tmp = current->next;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	ft_free_heredock(shelly, tmp, current);
	if (ft_parser(shelly) == 0)
	{
		if (exec_heredoc(shelly, shelly->ast) == 0)
			ft_exec(shelly, shelly->ast);
	}
	return (0);
}

void	exec_fork_heredoc(t_shelly *shelly, t_ast *node)
{
	pid_t	pid;
	int		fd_in;

	fd_in = shelly->fd[0];
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
