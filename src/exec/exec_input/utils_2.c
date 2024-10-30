/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:07:53 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/30 16:09:02 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**fill_cmd(t_ast *node, char **cmd, int *index)
{
	int	j;

	j = 0;
	if (node->node_type == CMD)
	{
		while (node->value[++j])
			cmd[(*index)++] = ft_strdup(node->value[j]);
	}
	return (cmd);
}

char	**fill_cmd_cmd(t_ast *node, char **cmd, int *index)
{
	int	j;

	j = 0;
	if (node->node_type == CMD)
	{
		while (node->value[j])
		{
			cmd[(*index)++] = ft_strdup(node->value[j]);
			j++;
		}
	}
	return (cmd);
}
