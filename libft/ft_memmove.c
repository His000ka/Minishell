/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:37:59 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/26 14:13:03 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*fsrc;
	char	*fdst;

	fdst = (char *)dst;
	fsrc = (char *)src;
	if (!fdst && !fsrc)
		return (NULL);
	while (len > 0)
	{
		if (fdst < fsrc)
			*fdst++ = *fsrc++;
		len--;
		if (fdst > fsrc)
			fdst[len] = fsrc[len];
	}
	return (dst);
}

// int	main(void)
// {
// 	char	*str = NULL;
// 	char	*str1 = NULL;
//     char	*dst = NULL;
//     char	*dst1 = NULL;
// 	size_t	i = 1;

// 	printf("<%s>\n", ft_memmove(dst, str, i));
// 	printf("<%s>\n", memmove(dst1, str1, i));
// }
