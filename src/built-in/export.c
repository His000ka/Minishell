/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:20:34 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/05 12:54:09 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_export(char **str)
{
	if (strncmp(str[1], "export", 6) == 0)
		return (1);
	return (0);
}

void	ft_export(char **envp)
{
	   while (*envp != NULL) {
        printf("declare -x %s\n", *envp);
        envp++;
    }
}

int main(int ac, char **av, char **envp) {

	if(if_export(av) == 1)
		ft_export(envp);
    return 0;
}