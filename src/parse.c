/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:07:44 by pitroin           #+#    #+#             */
/*   Updated: 2024/09/04 15:51:24 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(t_shelly *shelly)
{
	int	i;

	i = -1;
	while (shelly->cmd[++i] != '\0')
	{
		if (shelly->cmd[i] == 34)
		{
			i++;
			while (shelly->cmd[i] != 34 && shelly->cmd[i] != '\0')
				i++;
			if (shelly->cmd[i] != 34)
				return (1);
		}
		else if (shelly->cmd[i] == 39)
		{
			i++;
			while (shelly->cmd[i] != 39 && shelly->cmd[i] != '\0')
				i++;
			if (shelly->cmd[i] != 39)
				return (1);
		}
	}
	return (0);
}

void	init_token(t_shelly *shelly)
{
	int		i;
	t_token	*current;
	t_token	*previous;

	shelly->str = ft_split(shelly->cmd, ' ');
	if (!shelly->str)
		return ;
	previous = NULL;
	i = -1;
	while (shelly->str[++i])
	{
		current = malloc(sizeof(t_token));
		if (!current)
			return ;
		current->type = 0; //creer fonction pour le type de token
		current->str = ft_strdup(shelly->str[i]);
		current->prev = previous;
		current->next = NULL;
		if (previous)
			previous->next = current;
		else
			shelly->token = current;
		previous = current;
	}
}

void	ft_free(t_shelly *shelly)
{
	int	i;
	t_token	*current_token;
	t_token	*next_token;

	if (shelly->str)
	{
		i = -1;
		while (shelly->str[++i])
			free(shelly->str[i]);
		free(shelly->str);
		shelly->str = NULL;
	}
	if (shelly->token && ft_strlen(shelly->cmd) > 0)
	{
		current_token = shelly->token;
		while (current_token != NULL)
		{
			next_token = current_token->next;
			if (current_token->str)
				free(current_token->str);
			free(current_token);
			current_token = next_token;
		}
		shelly->token = NULL;
	}
	if (shelly->env != NULL)
	{
		if (shelly->env->envp != NULL)
			free_envp(shelly->env);
		free(shelly->env);
		shelly->env = NULL;
	}
	if (shelly->cmd != NULL)
	{
		free(shelly->cmd);
		shelly->cmd = NULL;
	}
}

void	affiche_token(t_shelly *shelly)
{
	t_token	*current_token;

	current_token = shelly->token;
	while (current_token != NULL)
	{
		printf("->%s\n", current_token->str);
		current_token = current_token->next;
	}
}


int	ft_parse(t_shelly *shelly)
{
	if (check_quote(shelly) == 1)
		return (ft_error("FAIL QUOTE\n", shelly));
	if (!shelly->cmd || ft_strlen(shelly->cmd) == 0)
		return (1);
	shelly->token = malloc(sizeof(t_token));
	if (!shelly->token)
		return (ft_error("ERROR INIT TOKEN\n", shelly));
	if (!shelly->str)
		init_token(shelly);
	// affiche_token(shelly);
	return (0);
}
