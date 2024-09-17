/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:20 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/17 17:29:36 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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


