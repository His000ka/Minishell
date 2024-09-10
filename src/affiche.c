/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:46 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/10 11:19:12 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	affiche_elem(t_shelly *shelly)
{
	int	j;

	j = -1;
	while (shelly->str[++j])
		printf("elem: >%s<\n", shelly->str[j]);
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

void	affiche_env_list(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("Content: %s\n", tmp->content);
		printf("Value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}
