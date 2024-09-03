/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:21:29 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 17:51:23 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

// int main()
// {
//     int my_data = 42;
//     t_list *my_list = ft_lstnew(&my_data);

//     if (my_list != NULL)
//         printf("%d\n", *(int *)my_list->content);
//     else
//         printf("Erreur\n");
//     free(my_list);
//     return 0;
// }
