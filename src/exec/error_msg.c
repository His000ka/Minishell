/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:06:36 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 10:06:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	msg_not_file(t_ast *node)
{
	if (node == NULL || node->value == NULL || node->value[0] == NULL)
	{
		write(STDERR_FILENO, "bash: Unknown error\n", 20);
		return;
	}
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, node->value[0], ft_strlen(node->value[0]));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
}

void	msg_cmd_not_found(t_ast *node)
{
	if (node == NULL || node->value == NULL || node->value[0] == NULL)
	{
		write(STDERR_FILENO, "bash: Unknown error\n", 20);
		return;
	}
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, node->value[0], ft_strlen(node->value[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
}