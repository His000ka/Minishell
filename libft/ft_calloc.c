/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:47:35 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/29 14:32:56 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	tot;

	tot = count * size;
	if ((size != 0 && (tot / size) != count) || tot > INT_MAX)
		return (NULL);
	p = malloc(tot);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, tot);
	return (p);
}

// int main(void)
// {
// 	int size = 10;
// 	size_t count = 0;
//     void * d1 = ft_calloc(count, size);
//     void * d2 = calloc(count, size);
//     if (memcmp(d1, d2, count * size))
//         printf("TEST_FAILED");
//     free(d1);
//     free(d2);
//     printf("TEST_SUCCESS");
//     return 0;
// }
