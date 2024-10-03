/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:33 by firdawssema       #+#    #+#             */
/*   Updated: 2024/09/30 20:14:26 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = -1;
// 	while (src[++i] != '\0')
// 		dest[i] = src[i];
// 	dest[i] = '\0';
// 	return (dest);
// }

int is_absolute_or_relative(char *cmd)
{
    return (cmd[0] == '/' || cmd[0] == '.');
}

char *path_concat(char *dir, char *cmd)
{
    int len_dir = ft_strlen(dir);
    int len_cmd = ft_strlen(cmd);
    char *full_path = malloc(len_dir + len_cmd + 2);
    if (!full_path)
        return NULL;
    ft_strcpy(full_path, dir);
    full_path[len_dir] = '/';
    ft_strcpy(full_path + len_dir + 1, cmd);

    return full_path;
}

int is_executable(char *path)
{
    struct stat sb;

    if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
        return 1;
    return 0;
}

char *find_executable_in_path(char *cmd)
{
    char *path_env = getenv("PATH");
    char *path_token;
    char *full_path = NULL;

    if (!path_env)
        return NULL;
    char *path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;
    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        full_path = path_concat(path_token, cmd);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }
        if (is_executable(full_path))
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int	exec_cmd_path(char *cmd, char **args, char **envp)
{
    char *path = NULL;

    if (is_absolute_or_relative(cmd))
		path = cmd;
	else
	{
		path = find_executable_in_path(cmd);
		if (!path)
		{
			printf("Command not found: %s\n", cmd);
			return (EXIT_FAILURE);
		}
	}
	if (fork() == 0)
	{
		if (execve(path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		wait(&status);
	}
	free (path);
	return (0);
}
