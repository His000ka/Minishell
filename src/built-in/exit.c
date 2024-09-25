/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:29:33 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/17 18:02:32 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_exit(char **str)
{
	if (ft_strcmp(str[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **str)
{
	int	is_num;

	if (str[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (is_numeric(str[1]) == 0)
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", str[1]);
		exit(255);
	}
	is_num = ft_atoi(str[1]);
	if (str[3] != NULL)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments");
		is_num = 1;
		return (1);
	}
	printf("exit\n");
	exit(is_num % 256);
}

// int	main(int ac, char **av)
// {
// 	if (if_exit(av) == 1)
// 		ft_exit(av);
// }
