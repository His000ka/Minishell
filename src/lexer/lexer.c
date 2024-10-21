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

char	*not_special_token(t_data_elem *data, char *val)
{
	char		*tmp;

	data->size = 0;
	while (val[data->i + data->size] != '$' && val[data->i + data->size] != '\''
		&& val[data->i + data->size] != '\"' && val[data->i + data->size] != '\0')
		data->size++;
	tmp = ft_strndup(&val[data->i], data->size);
	data->i += data->size;
	return (tmp);
}

char	*token_str(t_shelly *shelly, char *val)
{
	t_data_elem	data;
	char		*tmp1 = NULL;
	char		*tmp2 = NULL;
	char		*res = NULL;
	char		*res2 = NULL;

	data.i = 0;
	data.j = 0;
	if (ft_strchr(val, '$') == NULL && ft_strchr(val, '\'') == NULL
		&& ft_strchr(val, '\"') == NULL)
		return (ft_strdup(val));
	while (val[data.i] != '\0')
	{
		tmp1 = not_special_token(&data, val);
		if (!tmp1)
			tmp1 = ft_strdup("");
		if (val[data.i] == 34 || val[data.i] == 39)
			tmp2 = manage_quote(shelly, &data, val);
		else if (val[data.i] == '$')
			tmp2 = expender(shelly, &data, val);
		if (res)
		{
			res2 = ft_strdup(res);
			free(res);
			if (!tmp2)
				res = ft_strjoin(res2, tmp1);
			else
			{
				res = ft_strjoin(ft_strjoin(res2, tmp1), tmp2);
				free(tmp2);
				tmp2 = NULL;
			}
			free(res2);
		}
		else
		{
			res = ft_strjoin(tmp1, tmp2);
			free(tmp2);
			tmp2 = NULL;
		}
		if (tmp1)
			free(tmp1);
		printf("res: %s et data.i: %d\n", res, data.i);
		if (val[data.i] != '\0')
			data.i++;
	}
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
		printf("CREATE TOKEN\n");
		if (create_token(shelly, shelly->str[i]) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
