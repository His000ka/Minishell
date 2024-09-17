/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:20 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/12 22:39:02 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strjoin_pwd(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	// Allocate memory for both strings + '/' separator + null-terminator
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (p == NULL)
		return (NULL);
	i = 0;
	// Copy first string (s1)
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	// Add '/' separator
	p[i++] = '/';
	// Copy second string (s2)
	j = 0;
	while (s2[j] != '\0')
		p[i++] = s2[j++];
	// Null-terminate the string
	p[i] = '\0';
	return (p);
}


