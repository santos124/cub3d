/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:26:25 by wadina            #+#    #+#             */
/*   Updated: 2021/05/06 20:26:36 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (needle[0] == '\0')
		return (&((char *)haystack)[0]);
	while (i < ft_strlen(haystack) && i < len)
	{
		j = i;
		while (haystack[j] && needle[j - i] && (haystack[j] == needle[j - i]))
		{
			if (j < len)
			{	
				if (needle[j - i + 1] == '\0')
					return (&((char *)haystack)[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
