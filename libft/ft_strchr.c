/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:54:31 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 12:44:14 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (c >= 256)
		c -= 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i + 1]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

// int main(void)
// {
//     char  *test = NULL;
// 	char  *test1 = NULL;
//     int c = 'e' + 256;
//     printf("%s\n", ft_strchr(test, c));
//     printf("%s\n", strchr(test1, c));
// 	printf("%c\n", c);
//     return 0;
// }