/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:52 by marvin            #+#    #+#             */
/*   Updated: 2024/10/24 12:09:26 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*before_expend(char *input, t_data_elem *data)
{
	char	*tmp;

	data->size = 0;
	while (input[data->size] != '$' && input[data->size] != '\0')
		data->size++;
	tmp = ft_strndup(input, data->size);
	data->i += data->size;
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*expend_heredoc(t_shelly *shelly, char *input)
{
	char		*expend;
	char		*res;
	t_data_elem	data;

	data.i = 0;
	if (ft_strchr(input, '$') == NULL)
		return (ft_strdup(input));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[data.i] != '\0')
	{
		if (input[data.i] == '$')
			expend = ft_strjoin(res, expender(shelly, &data, input, 1));
		else
			expend = ft_strjoin(res, before_expend(input, &data));
		free(res);
		res = ft_strdup(expend);
		free(expend);
		expend = NULL;
	}
	return (res);
}

void	read_heredoc(t_shelly *shelly)
{
	char		*input;
	char		*expend;

	while (1)
	{
		input = readline("Heredoc>");
		if (ft_strcmp(input, shelly->delimiter) == 0)
		{
			free(input);
			break ;
		}
		expend = expend_heredoc(shelly, input);
		if (expend)
		{
			write(shelly->fd[1], expend, ft_strlen(expend));
			write(shelly->fd[1], "\n", 1);
			free(expend);
		}
		free(input);
	}
}

int	exec_heredoc_2(t_shelly *shelly, t_ast *node)
{
	t_ast	*node_exec;

	node_exec = NULL;
	if (pipe(shelly->fd) < 0)
		return (ft_error("pipe", 0, 0));
	node_exec = search_node_exec_heredoc(node);
	shelly->delimiter = search_delimiter(node);
	if (!shelly->delimiter)
		return (1);
	read_heredoc(shelly);
	free(shelly->delimiter);
	close(shelly->fd[1]);
	if (node->left && node->right->node_type == HEREDOC)
		return (adapt_cmd(shelly));
	else if (node->right->node_type == HEREDOC)
		return (adapt_cmd_2(shelly));
	if (!node_exec)
		return (1);
	exec_fork_heredoc_3(shelly, node, node_exec);
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
