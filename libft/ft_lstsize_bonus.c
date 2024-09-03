/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/17 14:22:14 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*copy;
	int		i;

	if (lst == NULL)
		return (0);
	i = 0;
	copy = lst;
	while (copy != NULL)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}

/*
int main()
{
    int a = 123;
    int b = 456;
    int c = 789;
    t_list *elem1 = ft_lstnew(&a);
    t_list *elem2 = ft_lstnew(&b);
    t_list *elem3 = ft_lstnew(&c);

    elem1->next = elem2;
    elem2->next = elem3;
    elem3->next = NULL;

    int size = ft_lstsize(elem1);
    printf("Taille de la liste : %d\n", size);

    return 0;
}*/
