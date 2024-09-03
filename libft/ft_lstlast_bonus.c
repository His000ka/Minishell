/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:33:51 by marvin            #+#    #+#             */
/*   Updated: 2024/04/17 14:20:29 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
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

//     t_list *last = ft_lstlast(elem1);
//      if (last != NULL)
//         printf("%d\n", *(int *)last->content);
//     return 0;
// }
