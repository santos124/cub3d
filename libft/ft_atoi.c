/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 04:10:42 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/03 04:10:45 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\n' || c == '\t' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;

	i = 0;
	n = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (n > 255 || n < 0)
			return (-1);
		n = n * 10 + (str[i++] - '0');
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (-1);
	return ((int)n);
}
