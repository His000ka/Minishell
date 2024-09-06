/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:26:43 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/05 12:59:14 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// int	find_type_token(t_shelly *shelly, char *str)
// {
// 	int		i;
// 	char	*copy;

// 	i = -1;
// 	while (str[++i] != '\0')
// 	{
// 		if (is_co(str[i]))
// 		{
			
// 		}
// 	}
// }

char	*join_char(char *str, char c)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = c;
	res[++i] = '\0';
	return (res);
}

void	split_command(t_shelly *shelly)
{
	int	size;

	size = 0;
	size += count_elem(shelly, size);
	printf("size : %d\n", size);
	// shelly->str = malloc(sizeof(char *) * (size + 1));
	// if (!shelly->str)
	// 	return ;
}

void	affiche_token(t_shelly *shelly)
{
	t_token	*current_token;

	current_token = shelly->token;
	while (current_token != NULL)
	{
		printf("->%s ->%d\n", current_token->str, current_token->type);
		current_token = current_token->next;
	}
}


int	ft_parse(t_shelly *shelly)
{
	if (check_cmd(shelly) > 0)
		return (1);
	if (!shelly->cmd || ft_strlen(shelly->cmd) == 0)
		return (1);
	// shelly->token = malloc(sizeof(t_token));
	// if (!shelly->token)
		// return (ft_error("ERROR INIT TOKEN\n", shelly));
	if (!shelly->str)
		split_command(shelly);
	// affiche_token(shelly);
	return (0);
}
