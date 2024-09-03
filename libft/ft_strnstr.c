/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 09:09:46 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 15:00:29 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char	*sm1;
	char	*sm2;
	size_t	i;
	size_t	ls2;

	i = 0;
	sm1 = (char *)s1;
	sm2 = (char *)s2;
	if (!s1 && len == 0)
		return (NULL);
	ls2 = ft_strlen(sm2);
	if (sm2 == 0 || s2[0] == 0)
		return (sm1);
	while (sm1[i] != '\0' && len >= i + ls2)
	{
		if (ft_strncmp(&sm1[i], sm2, ls2) == 0)
			return (&sm1[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     char    *s1 = "AAAAAAAAAAAAA";
//     char    *s2 = "A";
//     size_t len = ft_strlen(s1);
//     printf("%s\n", ft_strnstr(s1, s2, len));
//     printf("%s\n", strnstr(s1, s2, len));
//     return 0;;
// }
