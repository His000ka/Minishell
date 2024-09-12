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

// #include "../../include/minishell.h"

// int	token_len_left(t_token *token)
// {
// 	int	count;
// 	t_token	*tmp;

// 	count = 1;
// 	tmp = token;
// 	while (tmp != NULL)
// 	{
// 		if (is_cmd(tmp->type) == 1)
// 			return (count);
// 		count++;
// 		tmp = tmp->prev;
// 	}
// }

// int	token_len_right(t_token *token)
// {
// 	int	count;
// 	t_token	*tmp;

// 	count = 1;
// 	tmp = token;
// 	while (tmp != NULL)
// 	{
// 		if (is_cmd(tmp->type) == 1)
// 			return (count);
// 		count++;
// 		tmp = tmp->next;
// 	}
// }

// int	ft_search_pipe(t_shelly *shelly)
// {
// 	t_token	*tmp;

// 	tmp = shelly->token;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	while (tmp->prev != NULL && tmp->type != PIPE)
// 		tmp = tmp->prev;
// 	if (tmp->type == PIPE)
// 		return (0);
// 	return (1);
// }

// void	create_node_ast(int	node_type, char **value)
// {
// 	t_ast *new_node = malloc(sizeof(t_ast));
//     if (!new_node)
//     {
//         ft_error("ERROR ALLOCATING TOKEN\n", 0, 0);
//         return NULL;
//     }
//     new_node->value = value;
//     new_node->node_type = node_type;
//     new_node->right = NULL;
//     new_node->left = NULL;
//     return new_node;
// }

// void	ft_create_ast(t_shelly *shelly)
// {
// 	t_token	*tmp;

// 	tmp = shelly->token;
// 	while (tmp)
// 	{
// 		if (ft_search_pipe(shelly) == 0)
// 		{
			
// 		}
// 		tmp = tmp->next;
// 	}	
// }
