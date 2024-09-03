/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:46:37 by pitroin           #+#    #+#             */
/*   Updated: 2024/04/26 12:16:04 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}

// int main(void)
// {
// 	char	s[] = "test";
// 	size_t n = 2;
// 	bzero(s, n);
// 	return 0;
// }
