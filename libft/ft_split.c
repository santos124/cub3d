/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 09:28:47 by wadina            #+#    #+#             */
/*   Updated: 2021/05/08 09:28:50 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_liberator(char **ss, unsigned int j)
{
	while (j)
	{
		free(ss[j--]);
	}
	free(ss);
}

static int	ft_len_c(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) == c)
	{
		i++;
	}
	return (i);
}

static char	**ft_separator(char **ss, const char *s, int c)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	size_t	l;

	j = 0;
	i = 0;
	tmp = 0;
	while (i < ft_strlen(s) && ft_strlen(s) > 0)
	{
		if ((((*(s + i + 1) == c) || (*(s + i + 1) == 0)) && s[i] != c))
		{
			l = ft_len_c(&s[tmp], c);
			*(ss + j) = ft_substr(s, l + tmp, i + 1 - tmp - l);
			tmp = i + 1;
			if (ss[j] == NULL)
			{
				ft_liberator(ss, j);
				return (ss);
			}
			j++;
		}
		i++;
	}
	return (ss);
}

static int	ft_num_str(char const *s, int c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && *(s + i - 1) == c)
		{
			j++;
		}
		i++;
	}
	if (i != 0 && s[ft_strlen(s) - 1] != c && j != 0 && s[0] != c)
		j++;
	if (i != 0 && s[ft_strlen(s) - 1] != c && j == 0)
		j++;
	if (i != 0 && j == 0)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**ss;

	if (!s)
		return (NULL);
	i = ft_num_str(s, c);
	ss = (char **)ft_calloc(i + 1, sizeof(char *));
	if (ss == NULL)
		return (NULL);
	ft_separator(ss, s, c);
	return (ss);
}
