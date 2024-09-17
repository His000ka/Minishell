/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:25:23 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/17 15:26:01 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		p[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

// int main(void)
// {
//     char const  *s1 = NULL;
//     char const  *s2 = NULL;
//     printf("<%s>\n", ft_strjoin(s1, s2));
//     return 0;
// }
