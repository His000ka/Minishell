/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:13:46 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 10:40:45 by fimazouz         ###   ########.fr       */
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
	path = ft_strjoin(pwd, str[1]);
		
	if(chdir(path) != 0)
		perror("Problem with chdir\n");
	pwd = getcwd(NULL, 0);
}

int	main(int ac, char **av)
{
	
}
