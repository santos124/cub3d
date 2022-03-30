/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:23:58 by wadina            #+#    #+#             */
/*   Updated: 2021/05/06 20:24:11 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1)
		return (NULL);
	s3 = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (NULL == s3)
		return (NULL);
	ft_strlcpy(s3, s1, 1 + ft_strlen(s1));
	ft_strlcpy(&(s3[ft_strlen(s3)]), s2, 1 + ft_strlen(s2));
	return (s3);
}
