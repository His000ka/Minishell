/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:45:47 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/27 12:42:54 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	del(void *content)
// {
// 	free(content);
// }

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*copy;
	t_list	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	copy = *lst;
	while (copy != NULL)
	{
		next = copy->next;
		del(copy->content);
		free(copy);
		copy = next;
	}
	*lst = NULL;
}

// int main()
// {
//     int a = 123;
//     int b = 456;
//     int c = 777;
//     t_list *elem1 = ft_lstnew(&a);
//     t_list *elem2 = ft_lstnew(&b);
//     t_list *elem3 = ft_lstnew(&c);

//     elem1->next = elem2;
//     elem2->next = elem3;
//     elem3->next = NULL;

// 	ft_lstclear(&elem2, del);
//     return 0;
// }