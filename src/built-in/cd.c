/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:53 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/22 14:44:25 by fimazouz         ###   ########.fr       */
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
	char		*oldpwd;
	t_shelly	*shelly;

	shelly = get_shelly();
	oldpwd = getenv("OLDPWD");
	if (!oldpwd || shelly->oldpwd_count == 0)
	{
		printf("bash: cd: OLDPWD not set\n");
		shelly->oldpwd_count = 1;
		return (NULL);
	}
	return (oldpwd);
}

void	ft_cd(char **str)
{
	char		*pwd;
	char		*path;
	t_shelly	*shelly;

	shelly = get_shelly();
	pwd = getcwd(NULL, 0);
	if (!str[1] || ft_strcmp(str[1], "~") == 0)
		path = getenv("HOME");
	else if (ft_strcmp(str[1], "-") == 0)
	{
		path = get_oldpwd();
		if (!path)
			return (free(pwd));
		printf("%s\n", path);
	}
	else
		path = str[1];
	if (chdir(path) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		shelly->exit_code = 1;
	}
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
