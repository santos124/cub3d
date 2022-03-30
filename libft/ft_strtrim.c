/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:27:12 by wadina            #+#    #+#             */
/*   Updated: 2021/05/08 09:28:38 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_kl(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		kl;
	size_t		kr;

	i = 0;
	kl = 0;
	kr = 0;
	while (ft_strchr(set, s1[i]) && i < ft_strlen(s1))
	{
		kl++;
		i++;
	}
	j = ft_strlen(s1) - 1;
	return (kl);
}

static size_t	ft_kr(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		kl;
	size_t		kr;

	i = 0;
	kl = 0;
	kr = 0;
	while (ft_strchr(set, s1[i]) && i < ft_strlen(s1))
	{
		kl++;
		i++;
	}
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) && j > i)
	{
		kr++;
		j--;
	}
	return (kr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	j;
	int		tmp;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (s1[0] == 0)
	{
		tmp = 1 + ft_strlen(s1) - ft_kl(s1, set) - ft_kr(s1, set);
	}
	else
		tmp = ft_strlen(s1) - ft_kl(s1, set) - ft_kr(s1, set);
	s2 = ft_substr(s1, ft_kl(s1, set), tmp);
	if (s2 == NULL)
		return (NULL);
	if (s1[0] == 0)
	{
		return ((char *)s2);
	}
	return (s2);
}
