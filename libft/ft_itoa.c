/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 09:27:44 by wadina            #+#    #+#             */
/*   Updated: 2021/05/08 09:28:20 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_str(char *s, int n, int len)
{
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		if (n == -2147483648)
		{
			n = n + 2000000000;
			s[1] = '2';
		}
		n = -n;
	}
	while (n > 0)
	{
		s[len] = (n % 10) + '0';
		len--;
		n = n / 10;
	}
	return (s);
}

static int	ft_len(int n)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{	
		if (n == -2147483648)
			return (11);
		n = -n;
		sign = -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s;

	len = ft_len(n);
	s = ft_calloc(len + 1, sizeof(char));
	if (s == NULL)
		return (NULL);
	s = ft_str(s, n, len - 1);
	return (s);
}
