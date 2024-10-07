/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:31 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/02 23:06:12 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_pwd(char *str)
{
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	return (0);
}

void	ft_pwd(char **str)
{
	char *cwd;
	int i = 1;

	while (str[i])
	{
		if (str[i][0] == '-')
		{
			printf("bash: pwd: %s: invalid option\n", str[i]);
			return;
		}
		i++;
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("pwd");
}

// int	main(int ac, char **av)
// {
// 	if (if_pwd(av))
// 		ft_pwd();
// 	else
// 		printf("Commande inconnue : %s\n", av[1]);
// 	return (0);
// }