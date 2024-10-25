/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:57:41 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/25 18:41:41 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	transform_value_2(t_ast *node)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(node->value[0]);
	tmp2 = ft_strdup(node->value[1]);
	free(node->value[0]);
	free(node->value[1]);
	node->value[0] = ft_strdup(tmp2);
	node->value[1] = ft_strdup(tmp);
	free(tmp);
	free(tmp2);
}

void	transform_value(t_shelly *shelly, t_ast *node)
{
	char	*tmp;
	int		i;

	if (!node->value[1])
		return ;
	if (!node->value[2])
		transform_value_2(node);
	else
	{
		i = 0;
		free(node->value[0]);
		while (node->value[++i])
		{
			tmp = ft_strdup(node->value[i]);
			free(node->value[i]);
			node->value[i] = NULL;
			node->value[i - 1] = ft_strdup(tmp);
		}
	}
	ft_exec(shelly, node);
}

void	input_form_special(t_shelly *shelly, t_ast *node, int fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_in);
		transform_value(shelly, node->right);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, fd_in, pid);
	else
		exit(EXIT_FAILURE);
}

void	exec_input_classic(t_shelly *shelly, t_ast *node, int fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_in);
		if (node->left)
			ft_exec(shelly, node->left);
		exit(shelly->exit_code);
	}
	else if (pid > 0)
		pid_pos(shelly, fd_in, pid);
	else
		exit(EXIT_FAILURE);
}

void	exec_input_rec(t_shelly *shelly, t_ast *node)
{
	int		fd_in;
	t_ast	*left;
	t_ast	*current;
	pid_t	pid;
	int		i;

	if (node->left == NULL)
		return ;
	left = node->left;
	current = node;
	while (current->right->node_type == INPUT)
	{
		current = current->right;
		i = 0;
		while (current->left->value[i])
		{
			fd_in = open(current->left->value[i], O_RDONLY);
			if (fd_in == -1)
				msg_not_file(shelly, current->left->value[i]);
			i++;
			close(fd_in);
		}
	}
	if (current->right->node_type == CMD)
	{
		i = 0;
		while (current->right->value[i])
		{
			fd_in = open(current->right->value[i], O_RDONLY);
			if (fd_in == -1)
				msg_not_file(shelly, current->right->value[i]);
			i++;
			if (current->right->value[i])
				close(fd_in);
		}
		pid = fork();
		if (pid == 0)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(fd_in);
			ft_exec(shelly, left);
			exit(shelly->exit_code);
		}
		else if (pid > 0)
			pid_pos(shelly, fd_in, pid);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		i = 0;
		while (current->right->left->value[i])
		{
			fd_in = open(current->right->left->value[i], O_RDONLY);
			if (fd_in == -1)
				msg_not_file(shelly, current->right->left->value[i]);
			i++;
			if (current->right->left->value[i])
				close(fd_in);
		}
		pid = fork();
		if (pid == 0)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(fd_in);
			ft_exec(shelly, current->right);
			exit(shelly->exit_code);
		}
		else if (pid > 0)
			pid_pos(shelly, fd_in, pid);
		else
			exit(EXIT_FAILURE);
	}
}

void	exec_input(t_shelly *shelly, t_ast *node)
{
	int		fd_in;

	if (node->right->node_type == APPEND)
		return ;
	// if (node->right->node_type != CMD)
	// 	ft_exec(shelly, node->right);
	fd_in = open(search_value(node), O_RDONLY);
	if (fd_in == -1)
		return (msg_not_file(shelly, node->right->value[0]));	
	if (!node->left && node->right->node_type != INPUT)
		return (input_form_special(shelly, node, fd_in));
	else if (node->right->node_type != CMD)
		return (exec_input_rec(shelly, node));
	else if (node->left && !node->right->value[1])
		return (exec_input_classic(shelly, node, fd_in));
	else
		return (input_last_form(shelly, node));
}
