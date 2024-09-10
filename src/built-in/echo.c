/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:46:35 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 10:41:49 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_echo(char **str)
{
	if (ft_strncmp(str[1], "echo", 4) == 0)
		return (1);
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	option;
	
	i = 2;
	option = 0;

	if (str[i] && ft_strncmp(str[i], "-n", 2) == 0 && ft_strlen(str[i]) == 2)
	{
		option = 1;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (option == 0)
		printf("\n");
}

// int	main(int ac, char **av)
// {
// 	if (if_echo(av))
// 		ft_echo(av);
// 	return (0);
// }
