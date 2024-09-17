/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:46:35 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/12 13:27:52 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_echo(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	option;
	
	i = 1;
	option = 0;

	while (str[i] && ft_strncmp(str[i], "-n", 2) == 0)
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
// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		printf("Usage: %s [args]\n", argv[0]);
// 		return (1);
// 	}
	
// 	// Call the echo function with the command line arguments
// 	ft_echo(argv);

// 	return (0);
// }