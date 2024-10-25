/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:01:09 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/17 19:29:59 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	recup_value_1(t_ast *node)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	if (!node->value[1])
		return ;
	res = ft_strdup(node->value[1]);
	if (!res)
		return ;
	while (node->value[i])
	{
		free(node->value[i]);
		node->value[i] = NULL;
		i++;
	}
	node->value[0] = ft_strdup(res);
	return ;
}

void	exit_code_execve(t_shelly *shelly)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
		shelly->exit_code = WEXITSTATUS(status);
}

static int	ft_is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

static char	*ft_skip_delim(char *str, const char *delim)
{
	while (*str && ft_is_delim(*str, delim))
		str++;
	return (str);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*lasts = NULL;
	char		*token;

	if (str)
		lasts = str;
	if (!lasts)
		return (NULL);
	lasts = ft_skip_delim(lasts, delim);
	if (!*lasts)
		return (NULL);
	token = lasts;
	while (*lasts && !ft_is_delim(*lasts, delim))
		lasts++;
	if (*lasts)
	{
		*lasts = '\0';
		lasts++;
	}
	else
		lasts = NULL;
	return (token);
}
