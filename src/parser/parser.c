/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:38:31 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/12 15:49:11 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_cmd(int type)
{
	if (type == CMD || type == ARG)
		return (0);
	return (1);
}

int	check_pipeline(t_token *current)
{
	if (current->next == NULL || is_cmd(current->next->type) == 1)
	{
		printf("type: %d et val: %s\n", current->type, current->str);
		return (ft_error("ERROR PIPE\n", 0, 0));
	}
	return (0);
}

int	check_redirect(t_token *current)
{
	if (current->next == NULL || is_cmd(current->next->type) == 1)
	{
		printf("type: %d et val: %s\n", current->type, current->str);
		return (ft_error("ERROR REDIRECT\n", 0, 0));
	}
	return (0);
}

int	check_token(t_shelly *shelly)
{
	int	check;
	t_token *tmp;

	check = 0;
	tmp = shelly->token;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			check = check_pipeline(tmp);
		if (tmp->type == TRUNC || tmp->type == INPUT || tmp->type == APPEND || tmp->type == HEREDOC)
			check = check_redirect(tmp);
		tmp = tmp->next;
		if (check != 0)
			return (check);
	}
	return (check);
}

int		ft_parser(t_shelly *shelly)
{
	int		count;
	// t_token	*tmp;

	count = 1;
	if (check_token(shelly) > 0)
		return (1);
	// tmp = shelly->token;
	while (shelly->token)
	{
		count += is_cmd(shelly->token->type);
		shelly->token = shelly->token->next;
		// ft_create_ast(shelly);
	}
	return (0);
}