/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:27:25 by wadina            #+#    #+#             */
/*   Updated: 2021/05/08 09:29:20 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_len(const char *s, long start, long len)
{
	long int	i;

	i = start;
	while ((s[i] != 0) && i < (len + start))
		i++;
	return (i - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)ft_calloc(1 + (size_t)ft_len(s, start, len), sizeof(char));
	if (NULL == s2)
		return (NULL);
	if (start >= ft_strlen(s))
		return (s2);
	ft_strlcpy(s2, &s[start], ft_len(s, start, len) + 1);
	return (s2);
}
