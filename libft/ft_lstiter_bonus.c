/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:39:16 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/27 12:44:17 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void print_int(void *content)
// {
//     printf("%d\n", *(int *)content);
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// int main()
// {
//     int a = 10, b = 20, c = 30;
//     t_list *head = ft_lstnew(&a);
//     t_list *second = ft_lstnew(&b);
//     t_list *third = ft_lstnew(&c);

//     head->next = second;
//     second->next = third;

//     ft_lstiter(head, print_int);

//     return 0;
// }
