/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:49 by marvin            #+#    #+#             */
/*   Updated: 2024/04/29 12:12:49 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	res;

	if (fd < 0)
		return ;
	res = '0';
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			write(fd, "-", 1);
			ft_putnbr_fd(-n, fd);
		}
		return ;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	res = n % 10 + 48;
	write(fd, &res, 1);
}
/*
int main(void)
{
    ft_putnbr_fd(-21474836480);
    return 0;
}*/
