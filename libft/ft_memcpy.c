/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:02:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/26 14:04:11 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*fsrc;
	unsigned char		*fdst;

	fdst = dst;
	fsrc = src;
	if (!fsrc && !fdst)
		return (NULL);
	while (n)
	{
		*fdst++ = *fsrc++;
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	char	*str = NULL;
// 	char	*str1 = NULL;
//     char    *dst = NULL;
//     char    *dst1 = "";
// 	printf("%s\n", ft_memcpy(dst, str1, 5));
// 	printf("%s\n", memcpy(dst1, str1, 5));
// }
