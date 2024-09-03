/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:26:37 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 15:23:06 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	const unsigned char	*sm;
	size_t				i;

	i = 0;
	sm = s;
	while (i < size)
	{
		if (sm[i] == (unsigned char)c)
			return ((void *)&sm[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char    test[] = "test \0 abc";
// 	int     search = 'e';
// 	size_t s = 10;

// 	printf("%s\n", ft_memchr(test, search, s));
// 	printf("%s\n", memchr(test, search, s));
// 	return 0;
// }
