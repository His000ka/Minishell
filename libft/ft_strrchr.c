/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:06:07 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 13:00:16 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (c >= 256)
		c -= 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			j = i;
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	if (j != -1)
		return (&s[j]);
	return (NULL);
}

// int main(void)
// {
//     char  *test = "test de golemon";
//     int c = 1024;
//     printf("%s\n", ft_strrchr(test, c));
//     printf("%s\n", strrchr(test, c));
//     return 0;
// }
