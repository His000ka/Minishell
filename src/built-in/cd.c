/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:53 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/18 16:01:27 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_cd(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	return (0);
}

char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		printf("OLDPWD not set\n");
		return (NULL);
	}
	return (oldpwd);
}

void	ft_cd(t_shelly *shelly)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!shelly->ast->value[1] || ft_strcmp(shelly->ast->value[1], "~") == 0)
		path = getenv("HOME");
	else if (ft_strcmp(shelly->ast->value[1], "-") == 0)
	{
		path = get_oldpwd();
		if (!path)
		{
			free(pwd);
			return ;
		}
		printf("%s\n", path);
	}
	else
		path = shelly->ast->value[1];
	if (chdir(path) != 0)
		msg_not_file(shelly, path);
	free(pwd);
}

// void	ft_cd(char **str)
// {
// 	char	*pwd;
// 	char	*path;
// 	char	*new_pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (!str[1] || ft_strcmp(str[1], "~") == 0)
// 		path = getenv("HOME");
// 	else if (ft_strcmp(str[1], "-") == 0)
// 	{
// 		path = get_oldpwd();
// 		if (!path)
// 		{
// 			free(pwd);
// 			return;
// 		}
// 		printf("%s\n", path);
// 	}else
// 		path = str[1];
// 	if (chdir(path) != 0)
// 		perror("Problem with chdir");
// 	new_pwd = getcwd(NULL, 0);
// 	if (new_pwd)
// 	{
// 		printf("Directory changed to: %s\n", new_pwd);
// 		free(new_pwd);
// 	}
// 	else
// 		perror("Error retrieving new current directory");
// 	free(pwd);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		printf("Usage: %s [directory]\n", argv[0]);
// 		return (1);
// 	}

// 	// Print current working directory before change
// 	char *cwd = getcwd(NULL, 0);
// 	printf("Current Directory: %s\n", cwd);
// 	free(cwd);

// 	// Call the cd function with the provided directory
// 	ft_cd(argv);

// 	// Print current working directory after change
// 	cwd = getcwd(NULL, 0);
// 	printf("New Directory: %s\n", cwd);
// 	free(cwd);

// 	return (0);
// }
