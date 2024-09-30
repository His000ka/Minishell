/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:52 by marvin            #+#    #+#             */
/*   Updated: 2024/09/30 17:31:53 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_heredoc(t_shelly *shelly, t_ast *node)
{
	if (node->node_type == CMD)
		return (0);
	if (node->node_type == PIPE || node->node_type == TRUNC
		|| node->node_type == APPEND || node->node_type == INPUT)
		return (search_heredoc(shelly, node->right)
			|| search_heredoc(shelly, node->left));
	if (node->node_type == HEREDOC)
		return (exec_heredoc(shelly, node));
	return (0);
}

char	*search_delimiter(t_ast *node)
{
	t_ast	*current;
	char	*delimiter;

	current = node;
	while (current->right && current->right->left->node_type != CMD)
		current = current->right;
	delimiter = ft_strdup(node->right->left->value[0]);
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

void	read_heredoc(t_shelly *shelly)
{
	char	*input;
	char	*tmp;

	while (1)
	{
		input = readline("Heredoc>");
		if (ft_strcmp(input, shelly->delimiter) == 0)
		{
			free(input);
			break;
		}
		if (input)
		{
			tmp = ft_strjoin(shelly->buff_heredoc, input);
			free(shelly->buff_heredoc);
			shelly->buff_heredoc = ft_strdup(tmp);
			shelly->buff_heredoc = ft_strjoin(shelly->buff_heredoc, "\n");
			if (!shelly->buff_heredoc)
				return ;
			free(tmp);
		}
		free(input);
	}
}

int	exec_heredoc_not_token(t_shelly *shelly, t_ast  *node)
{
	shelly->delimiter = ft_strdup(node->right->value[0]);
	shelly->buff_heredoc = ft_strdup("");
	if (!shelly->buff_heredoc)
		return (ft_error("bash: syntax error near unexpected token 'newline'\n", 0, 0));
	read_heredoc(shelly);
	if (node->left->node_type != CMD)
		ft_exec(shelly, node->left);
	if (shelly->buff_heredoc)
	{
		printf("buffer_heredoc: %s", shelly->buff_heredoc);
		free(shelly->buff_heredoc);
	}
	return (0);
}

int	exec_heredoc_token(t_shelly *shelly, t_ast  *node)
{
	shelly->delimiter = search_delimiter(node);
	shelly->buff_heredoc = ft_strdup("");
	if (!shelly->buff_heredoc)
		return (ft_error("bash: syntax error near unexpected token 'newline'\n", 0, 0));
	read_heredoc(shelly);
	if (node->left->node_type != CMD)
		ft_exec(shelly, node->left);
	if (shelly->buff_heredoc)
	{
		printf("buffer_heredoc: %s", shelly->buff_heredoc);
		free(shelly->buff_heredoc);
	}
	return (0);
}

int	exec_heredoc(t_shelly *shelly, t_ast  *node)
{
	if (node->node_type != HEREDOC)
		return (0);
	if (node->right->node_type == CMD)
		exec_heredoc_not_token(shelly, node);
	else
		exec_heredoc_token(shelly, node);
	// exec_heredoc_2(shelly, node);
	free(shelly->delimiter);
	printf("Heredoc End\n");
	return (1);
}
