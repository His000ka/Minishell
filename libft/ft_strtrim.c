/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:44:06 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/26 13:57:17 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_check(char const *s1, char const *set, int f)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(set);
	i = 0;
	if (f == 1)
		i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != set[j] && j < len)
			j++;
		if (j == len)
			return (i);
		if (f == 1)
			i--;
		else
			i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	start;
	size_t	end;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) <= 0)
		return (ft_strdup(""));
	start = ft_check(s1, set, 0);
	end = ft_check(s1, set, 1) + 1;
	i = 0;
	if (start > end)
	{
		p = malloc(sizeof(char) * 1);
		p[i] = 0;
		return (p);
	}
	p = malloc(sizeof(char) * (end - start + 1));
	if (p == NULL)
		return (NULL);
	while (start < end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}
// int main(void)
// {
//     char const  *s1 = "";
//     char const  *set = "cdef";
//     // printf("%d\n", ft_check(s1, set, 0));
//     // printf("%d\n", ft_check(s1, set, 1));
//     printf("<%s>\n", ft_strtrim(s1, set));
//     return 0;
// }
