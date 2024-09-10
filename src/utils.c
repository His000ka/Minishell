/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:05:23 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/05 11:52:35 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_good_char(int c)
{
	if (c > 32 && c <= 126 && c != 34 && c != 39)
		return (1);
	return (0);
}

int	ft_error(char *str, char var, int nb)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (str[i] == '\'' && str[i - 1] == '\'')
		{
			while (nb-- > 0)
				write(1, &var, 1);
		}
		write(1, &str[i], 1);
	}
	return (1);
}

// int	ft_error(char *str, t_shelly *shelly)
// {
// 	if(!str)
// 		return(0);
// 	write(1, str, ft_strlen(str));
// 	// if (shelly->env != NULL)
// 	// {
// 	// 	if (shelly->env->envp != NULL)
// 	// 		free_envp(shelly->env);
// 	// 	free(shelly->env);
// 	// 	shelly->env = NULL;
// 	// }
// 	// if (shelly->cmd != NULL)
// 	// {
// 	// 	free(shelly->cmd);
// 	// 	shelly->cmd = NULL;
// 	// }
// 	return(1);
// }
