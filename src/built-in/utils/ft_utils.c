/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:20 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 10:42:26 by fimazouz         ###   ########.fr       */
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
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		p[i] = s1[i];
	p[++i] = '/';
	j = -1;
	while (s2[++j] != '\0')
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

char	*ft_strndup(const char *s, int n)
{
	char	*p;
	int		len;
	int		i;

	len = 0;
	while (s[len] != '\0')
		len++;
	if (len > n)
		len = n;
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
