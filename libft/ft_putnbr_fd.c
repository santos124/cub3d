/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:30:37 by wadina            #+#    #+#             */
/*   Updated: 2021/05/08 10:30:39 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9)
		ft_putnbr_fd((n - n % 10) / 10, fd);
	if (n > 9)
		ft_putnbr_fd((n - n % 10) / 10, fd);
	if (n < 0 && n >= -9)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = n + 2000000000;
			n = -n;
		}	
		else
		{
			n = -n;
		}
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n % 10 + '0', fd);
}
