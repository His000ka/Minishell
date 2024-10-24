/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachaoualim <rachaoualim@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:44:42 by marvin            #+#    #+#             */
/*   Updated: 2024/08/03 14:31:29 by rachaoualim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned long long int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

// int main(void)
// {
//     char    *test = "   -92233720368541775810amusetoi";
//     printf("%d\n", ft_atoi(test));
//     printf("%d\n", atoi(test));
//     return 0;
// }
