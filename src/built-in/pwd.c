/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:38:31 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 11:24:42 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_pwd(char *str)
{
	// if (ft_strncmp(str[1], "pwd", 3) == 0 && (str[2] == NULL))
	// 	return (1);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return (0);
}

void	ft_pwd(void)
{
	char	*cwd;
	char	*buffer;
	size_t	size;

	size = 1024;
	buffer = (char *)malloc(sizeof(char) * size);
	if (!buffer)
	{
		perror("malloc");
		return ;
	}
	cwd = getcwd(buffer, size);
	if (cwd)
		printf("%s\n", cwd);
	else
		perror("getcwd");
	free(buffer);
}

// int	main(int ac, char **av)
// {
// 	if (if_pwd(av))
// 		ft_pwd();
// 	else
// 		printf("Commande inconnue : %s\n", av[1]);
// 	return (0);
// }