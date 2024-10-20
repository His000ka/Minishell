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

#include "../../include/minishell.h"

int	type_token(char *val)
{
	if (is_pipe(val, 1) == 1)
		return (PIPE);
	if (is_trunc(val, 1) == 1)
		return (TRUNC);
	if (is_trunc(val, 1) == 2)
		return (APPEND);
	if (is_input(val, 1) == 1)
		return (INPUT);
	if (is_input(val, 1) == 2)
		return (HEREDOC);
	else
		return (6);
}

t_token	*create_node(void)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		ft_error("ERROR ALLOCATING TOKEN\n", 0, 0);
		return (NULL);
	}
	new_node->str = NULL;
	new_node->type = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

char	*token_str(t_shelly *shelly, char *val)
{
	t_data_elem	data;
	char		*res;

	data.i = 0;
	data.j = 0;
	if (ft_strchr(val, '$') == NULL && ft_strchr(val, '\'') == NULL
		&& ft_strchr(val, '\"') == NULL)
		return (ft_strdup(val));
	while (val[data.i] != '\0')
	{
		if (val[data.i] == 34 || val[data.i] == 39)
		{
			res = manage_quote(shelly, &data, val);
			printf("val[data.i]; %c\n", val[data.i]);
			if (!res)
				return (NULL);
			data.j++;
		}
		if (val[data.i] == '$')
		{
			data.j++;
			expender(shelly, &data);
		}
		// if (val[data.i] != '\0')
		// {
		// 	res[data.i - 1] = val[data.i];
		// }
		data.i++;
	}
	// res[data.i] = '\0';
	return (res);
}

int	create_token(t_shelly *shelly, char *val)
{
	t_token	*new_token;
	t_token	*current;

	if (val == NULL)
		return (1);
	new_token = create_node();
	if (!new_token)
		return (1);
	new_token->str = token_str(shelly, val);
	new_token->type = type_token(val);
	if (!new_token->str)
		return (1);
	if (!shelly->token)
		shelly->token = new_token;
	else
	{
		current = shelly->token;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
	return (0);
}

int	ft_lexer(t_shelly *shelly)
{
	int	i;

	i = -1;
	if (check_quote(shelly) > 0)
		return (EXIT_FAILURE);
	if (!shelly->cmd || ft_strlen(shelly->cmd) == 0)
		return (EXIT_FAILURE);
	if (split_command(shelly) == 1)
		return (EXIT_FAILURE);
	if (!shelly->str)
		return (EXIT_FAILURE);
	while (shelly->str[++i] != NULL)
	{
		printf("create token: %s\n", shelly->str[i]);
		if (create_token(shelly, shelly->str[i]) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
