/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:04 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 12:54:30 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	if_unset(char *str)
{
	if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	return (0);
}

void ft_unset(t_env *env_list, char **str)
{
	char *node;

	node = str[2];
	while(env_list != NULL)
	{
		if(env_list->content == str[2])
		{
			env_list = NULL;
		}
		env_list = env_list->next;
	}
}