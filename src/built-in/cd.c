/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:53 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/12 22:42:07 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int 	if_cd(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	return (0);
}

void ft_cd(char **str)
{
	char *pwd;
	char *path;
	char *new_pwd;
	
	pwd = getcwd(NULL, 0);
	
	if (!str[2] || ft_strncmp(str[2], "~", 1) == 0)
		path = getenv("HOME");
	else
		path = str[2];

	if (chdir(path) != 0)
		perror("Problem with chdir");

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		printf("Directory changed to: %s\n", new_pwd);
		free(new_pwd);
	}
	else
		perror("Error retrieving new current directory");
	free(pwd);
}


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

