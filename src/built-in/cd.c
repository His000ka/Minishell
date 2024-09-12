/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:53 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/12 13:33:39 by fimazouz         ###   ########.fr       */
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

	pwd = getcwd(NULL, 0);
	path = ft_strjoin_pwd(pwd, str[1]);
		
	if(chdir(path) != 0)
		perror("Problem with chdir\n");
	pwd = getcwd(NULL, 0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s [directory]\n", argv[0]);
		return (1);
	}

	// Print current working directory before change
	char *cwd = getcwd(NULL, 0);
	printf("Current Directory: %s\n", cwd);
	free(cwd);

	// Call the cd function with the provided directory
	ft_cd(argv);

	// Print current working directory after change
	cwd = getcwd(NULL, 0);
	printf("New Directory: %s\n", cwd);
	free(cwd);

	return (0);
}

