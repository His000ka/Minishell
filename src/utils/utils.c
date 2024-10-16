/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:45:25 by fimazouz          #+#    #+#             */
/*   Updated: 2024/10/16 16:45:25 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*ft_strsearch(char *s, int c, int flag)
{
	int	i;

	i = 0;
	c %= 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (flag == 0)
				return (ft_strndup(s + i + 1, ft_strlen(s + i + 1)));
			else if (flag == 1)
				return (ft_strndup(s, i));
		}
		i++;
	}
	if (flag == 1)
		return (ft_strndup(s, ft_strlen(s)));
	return (NULL);
}

int	ft_error(char *str, char var, int nb)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (str[i] == '\'' && str[i - 1] == '\'')
		{
			while (nb-- > 0)
				write(1, &var, 1);
		}
		write(1, &str[i], 1);
	}
	return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
