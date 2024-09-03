/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:55:38 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/26 14:58:10 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	char			*fsrc;
	char			*fdest;
	unsigned int	lendst;
	unsigned int	lensrc;

	i = 0;
	fsrc = (char *) src;
	fdest = (char *) dest;
	if (!fdest && dstsize == 0)
		return (ft_strlen(fsrc));
	lendst = ft_strlen(fdest);
	lensrc = 0;
	while (fsrc[lensrc] && lensrc + lendst + 1 < dstsize)
		lensrc++;
	while (src[i] && lensrc > i)
	{
		dest[lendst + i] = src[i];
		i++;
	}
	dest[lendst + i] = '\0';
	if (dstsize < lendst)
		return (ft_strlen(fsrc) + dstsize);
	return (ft_strlen(fsrc) + lendst);
}

// int	main(void)
// {
// 	char	a[600] = "Hello";
// 	char	b[] = "testtropcool";
// 	char	c[600] = "Hello";
// 	size_t n = 0;

// 	printf("%zu ", ft_strlcat(a, b, n));
// 	printf("%s\n", a);
// 	printf("%lu ", strlcat(c, b, n));
// 	printf("%s", c);
// }
