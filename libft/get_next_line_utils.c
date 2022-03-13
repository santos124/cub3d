/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:08:52 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:08:54 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoi(char *s1, char *s2, size_t s2len)
{
	char	*s3;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + s2len + 1));
	if (s3 == NULL)
		return (NULL);
	ft_memset(s3, 0, ft_strlen(s1) + s2len + 1);
	ft_memmove(s3, s1, ft_strlen(s1));
	ft_memmove(&(s3[ft_strlen(s1)]), s2, s2len);
	s3[ft_strlen(s1) + s2len] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}

int	ft_index(char *s, char c)
{
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
