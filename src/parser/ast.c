// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ast.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/12 13:57:56 by pitroin           #+#    #+#             */
// /*   Updated: 2024/09/12 15:04:48 by pitroin          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../include/minishell.h"

void	print_ast(t_ast *node, int level)
{
    if (!node)
        return;
    // Indentation pour afficher les niveaux
    for (int i = 0; i < level; i++) {
        printf("    ");  // 4 espaces par niveau
    }

    // Afficher le type de nœud
    if (node->node_type == CMD) {
        printf("Command: ");
        for (int i = 0; node->value[i] != NULL; i++) {
            printf("%s ", node->value[i]);
        }
        printf("\n");
    } else if (node->node_type == PIPE) {
        printf("Operator: |\n");
    } else if (node->node_type == INPUT) {
        printf("Operator: <\n");
    } else if (node->node_type == TRUNC) {
        printf("Operator: >\n");
    // } else if (node->node_type == AND) {
    //     printf("Operator: &&\n");
    // } else if (node->node_type == OR) {
    //     printf("Operator: ||\n");
    } else {
        printf("Unknown node type\n");
    }

    // Appel récursif pour les sous-arbres gauche et droit
    if (node->left) {
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("Left:\n");
        print_ast(node->left, level + 1);
    }

    if (node->right) {
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("Right:\n");
        print_ast(node->right, level + 1);
    }
}

int count_command_tokens(t_token *token)
{
    int count = 0;

    while (token && is_cmd(token->type) == 0) {
        count++;
        token = token->next;
    }

    return count;
}

char	**extract_command(t_token *token)
{
	int count;
	char	**cmd;
	int i;

	count = count_command_tokens(token);
	cmd = (char **)malloc((count + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token && is_cmd(token->type) == 0)
	{
		cmd[i++] = strdup(token->str);  //secu
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_ast *create_ast_node(char **value, int node_type)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = value;
	node->node_type = node_type;
	node->left = NULL;
	node->right = NULL;
    return (node);
}


t_ast	*create_ast(t_token *tokens)
{
	t_token	*current = tokens;
	t_ast	*root = NULL;
	t_ast	*new_node = NULL;

	while (current)
	{
        if (is_cmd(current->type) == 1)
		{
            new_node = create_ast_node(NULL, current->type);
            new_node->left = root;
            current = current->next;
            new_node->right = create_ast(current);
            return (new_node);
        }
        else
		{
            root = create_ast_node(extract_command(current), CMD);
            while (current && is_cmd(current->type) == 0)
                current = current->next;
        }
    }
    return (root);
}
