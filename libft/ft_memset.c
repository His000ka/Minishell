/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachaoualim <rachaoualim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:53:42 by pitroin           #+#    #+#             */
/*   Updated: 2024/08/03 09:51:40 by rachaoualim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;

	str = (char *)b;
	while (len > 0)
	{
		*str++ = c;
		len--;
	}
	return (b);
}

// int	main(void)
// {
// 	char	str[100];
// 	char	str1[100];
// 	char c = 'a';
// 	size_t n = 90;
// 	if (ft_memset(str, c, n) == memset(str1, c, n))
// 		printf("GG");
// 	else
// 		printf("FAIL");
// }
