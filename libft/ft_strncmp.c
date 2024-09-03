/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:11:20 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 17:08:18 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int main(void)
// {
//     char    *s1 = "\200";
//     char    *s2 = "test\0\0test";
//     int     n = 10;
//     printf("%d\n", ft_strncmp(s1, s2, n));
//     printf("%d\n", strncmp(s1, s2, n));
//     return 0;
// }
