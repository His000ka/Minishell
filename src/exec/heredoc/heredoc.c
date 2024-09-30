/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:10:52 by marvin            #+#    #+#             */
/*   Updated: 2024/09/29 10:10:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_heredoc(t_shelly *shelly, t_ast *node)
{
	printf("searching\n");
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

int	exec_heredoc(t_shelly *shelly, t_ast  *node)
{
	if (node->node_type != HEREDOC)
		return (search_heredoc(shelly, node));
	printf("Heredoc find\n");
	return (0);
}
