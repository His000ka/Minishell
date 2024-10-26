/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:23:53 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/26 14:12:42 by firdawssema      ###   ########.fr       */
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
	t_env		*current;

	shelly = get_shelly();
	oldpwd = NULL;
	current = shelly->env;
	while (current)
	{
		if (ft_strcmp(current->content, "OLDPWD") == 0)
		{
			oldpwd = current->value;
			break ;
		}
		current = current->next;
	}
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
	t_env		*current;
	char		*old;

	shelly = get_shelly();
	old = getcwd(NULL, 0);
	pwd = NULL;
	current = shelly->env;

	if (!str[1] || ft_strcmp(str[1], "~") == 0)
		path = getenv("HOME");
	else if (ft_strcmp(str[1], "-") == 0)
	{
		path = get_oldpwd();
		if (!path)
			return (free(old));
		printf("%s\n", path);
	}
	else
		path = str[1];
	if (chdir(path) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", str[1]);
		shelly->exit_code = 1;
		free(old);
		return ;
	}
	pwd = getcwd(NULL, 0);
	shelly->oldpwd_count = 1;
	while (current)
	{
		if (ft_strcmp(current->content, "OLDPWD") == 0)
		{
			if(old)
				current->value = ft_strdup(old);
		}else if (ft_strcmp(current->content, "PWD") == 0)
		{
			if(pwd)
				current->value = ft_strdup(pwd);	
		}
		current = current->next;
	}
	free(old);
	free(pwd);
}
