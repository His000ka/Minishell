/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:44:09 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/25 16:32:01 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**input_create_copy(t_ast *node, int size)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (node->left->value[i])
	{
		copy[i] = ft_strdup(node->left->value[i]);
		free(node->left->value[i]);
		i++;
	}
	j = 1;
	while (node->right->value[j])
	{
		copy[i] = ft_strdup(node->right->value[j]);
		i++;
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

void	input_last_form(t_shelly *shelly, t_ast *node)
{
	int		i;
	int		size;
	char	**copy;

	size = 0;
	i = 1;
	while (node->left->value[size])
		size++;
	while (node->right->value[i++])
		size++;
	copy = input_create_copy(node, size);
	if (copy == NULL)
		return ;
	i = 0;
	node->left->value = malloc(sizeof(char *) * (size + 1));
	while (copy[i])
	{
		node->left->value[i] = ft_strdup(copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
	copy = NULL;
	node->left->value[i] = NULL;
	ft_exec(shelly, node->left);
}
