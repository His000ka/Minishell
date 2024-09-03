/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:55:28 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 15:32:37 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ms1;
	const unsigned char	*ms2;
	size_t				i;

	ms1 = s1;
	ms2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ms1[i] == ms2[i] && i + 1 < n)
		i++;
	return (ms1[i] - ms2[i]);
}

// int main(void)
// {
//     char    *s1 = "\0";
//     char    *s2 = "tes";
//     size_t n = 0;
//     printf("%d\n", ft_memcmp(s1, s2, n));
//     printf("%d\n", memcmp(s1, s2, n));
//     return 0;
// }
