/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:04:49 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/29 11:47:28 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **p, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static int	ft_checktab(char const *s, char c, int k, int f)
{
	int	count;

	count = 0;
	while (s[k] == c)
		k++;
	if (f == 1)
		return (k);
	while (s[k] != '\0')
	{
		if (s[k] == c)
			return (count);
		k++;
		count++;
	}
	return (count);
}

static int	ft_checksize(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (0);
	count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			if (s[i] != '\0')
				count++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_split2(char const *s, char c, char **p, int lenp)
{
	int	k;
	int	j;
	int	i;
	int	lentab;

	i = -1;
	k = 0;
	while (++i < lenp)
	{
		j = -1;
		k = ft_checktab(s, c, k, 1);
		lentab = ft_checktab(s, c, k, 0);
		p[i] = malloc(sizeof(char) * (lentab + 1));
		if (p[i] == NULL)
			return (ft_free(p, i));
		while (++j < lentab)
			p[i][j] = s[k + j];
		k += j;
		p[i][j] = '\0';
	}
	if (i == -1)
		i = 0;
	p[i] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		lenp;

	if (s == NULL)
		return (NULL);
	lenp = ft_checksize(s, c);
	p = malloc(sizeof(char *) * (lenp + 1));
	if (p == NULL)
		return (ft_free(p, 0));
	p = ft_split2(s, c, p, lenp);
	return (p);
}

// int	main(void)
// {
// 	char		**test;
// 	char const	*s = "salut";
// 	char    c = ' ';
// 	int i = 0;
// 	test = ft_split(s, c);
// 	while (test[i] != NULL)
// 	{
// 		printf("<%s>\n", test[i]);
// 		free(test[i]);
// 		i++;
// 	}
// 	free(test);
// 	return 0;
// }
// int main(void)
// {
// 	char	**tabstr;
// 	if (!(tabstr = ft_split("", 'z')))
// 			printf("NULL");
// 	else
// 		if (!tabstr[0])
// 			printf("ok\n");
// }
