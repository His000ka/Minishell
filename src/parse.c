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

int	size_elem(t_shelly *shelly, int j, int f)
{
	int	i;
	int	res;
	int	count;

	i = 0;
	count = 0;
	res = 0;
	while (count <= j && shelly->cmd[i])
	{
		i += count_index(&shelly->cmd[i], 1);
		res = i + 1;
		i += is_quote(&shelly->cmd[i], 2);
		count += is_quote(&shelly->cmd[i], 0);
		if (j == count && f == 0)
			return (i - res);
		count++;
	}
	return (res);
}

void	add_elem(t_shelly *shelly, int count)
{
	int	size;
	int	j;
	int	i;
	int	k;

	j = -1;
	while (++j <= count)
	{
		size = size_elem(shelly, j, 0);
		shelly->str[j] = malloc(sizeof(char) * (size + 1));
		if (!shelly->str[j])
			return ;
		i = size_elem(shelly, j, 1);
		k = -1;
		while (++k < size)
			shelly->str[j][k] = shelly->cmd[k + i];
		shelly->str[j][k] = '\0';
	}
	shelly->str[j] = NULL;
	j = 0;
	while (shelly->str[j++])
	{
		printf("elem: >%s<\n", shelly->str[j]);
	}
	
}

void	split_command(t_shelly *shelly)
{
	int	count;

	count = 0;
	count += count_elem(shelly, count);
	printf("count : %d\n", count);
	// shelly->str = malloc(sizeof(char *) * (count + 1));
	// if (!shelly->str)
	// 	return ;
	// add_elem(shelly, count);
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
