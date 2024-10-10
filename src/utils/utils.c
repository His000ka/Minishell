/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/03 15:05:23 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/05 11:52:35 by pitroin          ###   ########.fr       */
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
	while (c >= 256)
		c -= 256;
	while (s[i] != '\0')
	{
		if (s[i] == c && flag == 0)
			return (ft_strndup((&s[i + 1]), i));
		else if (s[i] == c && flag == 1)
			return (ft_strndup(s, i));
		i++;
	}
	if (flag == 1)
		return (ft_strndup(s, ft_strlen(s)));
	if (c == '\0')
		return (&s[i]);
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
