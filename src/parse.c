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

void	split_cmd(t_shelly *shelly)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;

	i = -1;
	count = 1;
	tmp = ft_strdup("");
	while (shelly->cmd[++i])
	{
		if (shelly->cmd[i] == ' ' && (shelly->cmd[i + 1] != ' ' && shelly->cmd[i + 1] != '\0'))
			count++;
		if (shelly->cmd[i] == '|' && (shelly->cmd[i + 1] != '|' && shelly->cmd[i + 1] != '\0'))
			count++;
	}
	shelly->str = malloc(sizeof(char *) * (count + 1));
	if (!shelly->str)
		return ;
	i = -1;
	while (++i < count)
		shelly->str[i] = NULL;
	shelly->str[count] = NULL;
	i = -1;
	j = 0;
	while (shelly->cmd[i])
	{
		if (shelly->cmd[i] == ' ' && shelly->cmd[i + 1] != '\0')
		{
			while (shelly->cmd[i] == ' ')
				i++;
			if (shelly->cmd[i] != '\0')
				j++;
		}
		if (!shelly->str[j])
			ft_strdup("");
		while (shelly->cmd[i] != '|' && shelly->cmd[i] != ' ')
		{
			tmp = join_char(shelly->str[j], shelly->cmd[i]);
			free(shelly->str[j]);
			shelly->str[j] = tmp;
			free(tmp);
		}
		if (shelly->cmd[i] == '|' && shelly->cmd[i + 1] != '\0')
		{
			j++;
			if (!shelly->str[j])
				ft_strdup("");
			tmp = join_char(shelly->str[j], shelly->cmd[i]);
			free(shelly->str[j]);
			shelly->str[j] = tmp;
			free(tmp);
			if (shelly->cmd[i] != '\0')
			j++;
		}
	}
	i = -1;
	while (shelly->str[++i] != NULL)
		printf("%s\n", shelly->str[i]);
}

//leaks dans init_token
// void	init_token(t_shelly *shelly)
// {
// 	int		i;
// 	t_token	*current;
// 	t_token	*previous;

// 	shelly->str = ft_split(shelly->cmd, ' ');
// 	if (!shelly->str)
// 		return ;
// 	previous = NULL;
// 	i = -1;
// 	while (shelly->str[++i])
// 	{
// 		current = malloc(sizeof(t_token));
// 		if (!current)
// 		{
// 			ft_free_token(shelly->token);
// 			shelly->str = NULL;
// 			return ;
// 		}
// 		current->type = 0; //creer fonction pour le type de token
// 		current->str = ft_strdup(shelly->str[i]);
// 		if (!current->str)
// 		{
// 			free(current);
// 			ft_free_token(shelly->token);
// 			shelly->str = NULL;
// 			return ;
// 		}
// 		current->prev = previous;
// 		current->next = NULL;
// 		if (previous)
// 			previous->next = current;
// 		else
// 			shelly->token = current;
// 		previous = current;
// 	}
// }

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
	if (check_quote(shelly) == 1)
		return (ft_error("FAIL QUOTE\n", shelly));
	if (!shelly->cmd || ft_strlen(shelly->cmd) == 0)
		return (1);
	// shelly->token = malloc(sizeof(t_token));
	// if (!shelly->token)
		// return (ft_error("ERROR INIT TOKEN\n", shelly));
	if (!shelly->str)
		split_cmd(shelly);
	// affiche_token(shelly);
	return (0);
}
