/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:34:22 by pitroin           #+#    #+#             */
/*   Updated: 2024/10/20 15:36:15 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	affiche_ast(t_ast *node, int level)
{
	int	i;

	if (!node)
		return ;
	i = -1;
	while (++i < level)
		printf("    ");
	if (node->node_type == CMD)
	{
		printf("Command: ");
		i = 0;
		while (node->value[i] != NULL)
			printf("%s ", node->value[i++]);
		printf("\n");
	}
	else if (node->node_type == PIPE)
		printf("Operator: |\n");
	else if (node->node_type == INPUT)
		printf("Operator: <\n");
	else if (node->node_type == TRUNC)
		printf("Operator: >\n");
	else if (node->node_type == APPEND)
		printf("Operator: >>\n");
	else if (node->node_type == HEREDOC)
		printf("Operator: <<\n");
	else
		printf("Unknown node type\n");
	if (node->left)
	{
		i = -1;
		while (++i < level)
			printf("    ");
		printf("Left:\n");
		affiche_ast(node->left, level + 1);
	}
	if (node->right)
	{
		i = -1;
		while (++i < level)
			printf("    ");
		printf("Right:\n");
		affiche_ast(node->right, level + 1);
	}
}

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
