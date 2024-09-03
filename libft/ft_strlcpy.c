/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:56:16 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/17 15:27:26 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (dstsize <= 0)
		return (len);
	while (dstsize > 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		dstsize--;
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
int main(void)
{
	char	a[20] = "10";
	char	c[20] = "10";
	char	b[] = "Salut";
	size_t  n = 5;
	ft_strlcpy(a, b, n);
	// printf("%zu\n", ft_strlcpy(a, b, n));
	printf("%s\n", a);
    // printf("%lu\n", strlcpy(c, b, n));
	// printf("%s\n", c);
}*/
