/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:46:35 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/02 22:44:18 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_echo(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	return (0);
}

int	is_valid_option(char *str)
{
	int i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	ft_echo(char **str)
{
	int	i;
	int	option;
	
	i = 1;
	option = 0;
	while (str[i] && is_valid_option(str[i]))
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