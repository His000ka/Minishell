/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:20:00 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/16 14:20:00 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_absolute_or_relative(char *cmd)
{
	return (cmd[0] == '/' || cmd[0] == '.');
}

char	*path_concat(char *dir, char *cmd)
{
	int		len_dir;
	int		len_cmd;
	char	*full_path;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[len_dir] = '/';
	ft_strcpy(full_path + len_dir + 1, cmd);
	return (full_path);
}

int	is_executable(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (1);
	return (0);
}

char	*find_executable_in_path(t_shelly *shelly, char *cmd)
{
	char	*path_env;
	char	*path_token;
	char	*full_path;
	char	*path_copy;

	full_path = NULL;
	path_env = get_value_env(shelly, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	path_token = ft_strtok(path_copy, ":");
	while (path_token != NULL)
	{
		full_path = path_concat(path_token, cmd);
		if (!full_path)
			return (free(path_copy), NULL);
		if (is_executable(full_path))
			return (free(path_copy), full_path);
		free(full_path);
		path_token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	exec_cmd_path(char *cmd, char **args, t_shelly *shelly)
{
	char	*path;

	path = NULL;
	if (is_absolute_or_relative(cmd))
		path = ft_strdup(cmd);
	else
		path = find_executable_in_path(shelly, cmd);
	if (!path)
		return (EXIT_FAILURE);
	if (fork() == 0)
	{
		if (execve(path, args, shelly->envp) == -1)
			msg_is_or_not_dir(shelly, path);
	}
	else
		exit_code_execve(shelly);
	free(path);
	return (0);
}
