/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:30:46 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/14 10:30:46 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	msg_is_or_not_dir(t_shelly *shelly, char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			printf("bash: %s: is a directory\n", path);
	}
	else
		msg_not_file(shelly, path);
}

void	msg_permission(t_shelly *shelly, char *value)
{
	if (!value)
		return ;
	if (errno == EACCES)
		printf("bash: %s: Permission denied\n", value);
	else
		msg_not_file(shelly, value);
	shelly->exit_code = 1;
}

void	msg_not_file(t_shelly *shelly, char *value)
{
	if (value == NULL)
	{
		write(STDERR_FILENO, "bash: Unknown error\n", 20);
		return ;
	}
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	shelly->exit_code = 1;
}

void	msg_cmd_not_found(t_ast *node)
{
	if (node == NULL || node->value == NULL || node->value[0] == NULL)
	{
		write(STDERR_FILENO, "bash: Unknown error\n", 20);
		return ;
	}
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, node->value[0], ft_strlen(node->value[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
}
