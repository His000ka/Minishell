/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:01:40 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/27 11:45:39 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checksize(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i += 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i += 1;
	}
	return (i);
}

static char	*ft_intmin(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static char	*ft_itoa2(int n, char *str, int size)
{
	int	i;

	i = 1;
	if (n == 0)
		str[0] = '0';
	if (n == -2147483648)
		str = ft_intmin(str);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[size - i] = (n % 10) + 48;
		i++;
		n /= 10;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_checksize(n);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	return (ft_itoa2(n, str, size));
}

// int main(void)
// {
// 	int n = -2147483648LL;
// 	printf("%d\n", ft_checksize(n));
// 	printf("<%s>\n", ft_itoa(n));
// 	return 0;
// }
