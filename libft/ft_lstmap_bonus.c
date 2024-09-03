/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:45:22 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/29 12:01:08 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	del(void *content)
// {
// 	free(content);
// }
// void	*print_int(void *content)
// {
// 	*(int *)content *= 10;
// 	return (content);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy;
	t_list	*last;
	t_list	*newlst;

	last = NULL;
	newlst = NULL;
	while (lst != NULL && f != NULL && del != NULL)
	{
		copy = malloc(sizeof(t_list));
		if (copy == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		copy->content = f(lst->content);
		copy->next = NULL;
		if (last == NULL)
			newlst = copy;
		else
			last->next = copy;
		last = copy;
		lst = lst->next;
	}
	return (newlst);
}

// int main()
// {
//     int a = 10, b = 20, c = 30;
//     t_list *head = ft_lstnew(&a);
//     t_list *second = ft_lstnew(&b);
//     t_list *third = ft_lstnew(&c);

//     head->next = second;
//     second->next = third;

//     ft_lstmap(head, print_int, del);

//     return 0;
// }