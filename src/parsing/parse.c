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
	if (is_pipe(val, 0) == 1)
		return (PIPE);
	if (is_trunc(val, 0) == 1)
		return (3);
	if (is_input(val, 0) == 1)
		return (1);
	else
		return (6);
}

t_token *create_node(void)
{
    t_token *new_node = malloc(sizeof(t_token));
    if (!new_node)
    {
        ft_error("ERROR ALLOCATING TOKEN\n", 0, 0);
        return NULL;
    }
    new_node->str = NULL;
    new_node->type = 0;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void create_token(t_shelly *shelly, char *val)
{
    t_token *new_token;
    t_token *current;

    if (val == NULL)
    {
        ft_error("ERROR: Null value passed to create_token\n", 0, 0);
        return;
    }
    new_token = create_node();
    if (!new_token)
        return;
    new_token->str = ft_strdup(val);
	// new_token->type = type_token(val);
    if (!new_token->str)
    {
        // free(new_token);
        ft_error("ERROR COPYING STRING\n", 0, 0);
        return;
    }
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
}

int	ft_parse(t_shelly *shelly)
{
	int	i;

	i = -1;
	if (check_cmd(shelly) > 0)
		return (1);
	if (!shelly->cmd || ft_strlen(shelly->cmd) == 0)
		return (1);
	if (!shelly->str)
		split_command(shelly);
	while (shelly->str[++i] != NULL)
		create_token(shelly, shelly->str[i]);
	affiche_token(shelly);
	return (0);
}
