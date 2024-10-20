/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:19 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/18 13:56:36 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_free_heredock(t_shelly *shelly, t_token	*current, t_token	*tmp)
{
	free(current);
	free(tmp);
	free(shelly->ast);
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
