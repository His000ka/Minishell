/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:01:44 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/29 14:34:58 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	*del(void *content)
// {
// 	free(content);
// 	return (content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// int main(void)
// {
// 	t_list	*node = malloc(sizeof(t_list));
//     node->content = strdup("Hello, world!\n");
//     node->next = NULL;

// 	printf ("1%s\n", (char *)node->content);
// 	ft_lstdelone(node, (void *)del);
// 	printf ("2%s\n", (char *)node->content);
//     return 0;
// }
