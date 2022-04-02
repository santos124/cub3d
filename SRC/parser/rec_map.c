/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:56:27 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/02 23:56:29 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_map_size(t_parser *p)
{
	int		i;
	int		j;

	i = 0;
	if (!p->map)
		ft_error("Error: map error!", p);
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			j++;
			if (j > p->line)
				p->line = j;
		}
		i++;
	}
	p->col = i;
}

static char	*ft_realloc_mod(char *str, int num, char c)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (num + 1));
	if (!new)
		ft_error("Error: malloc error!", NULL);
	new = (char *)ft_memset(new, ' ', num);
	new[num] = '\0';
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (i < num)
	{
		new[i] = c;
		i++;
	}
	return (new);
}

void	rectangle_map(t_parser *p)
{
	int		i;
	void	*tmp;

	i = 0;
	tmp = NULL;
	check_map_size(p);
	while (p->map[i])
	{
		if ((int)ft_strlen(p->map[i]) < p->line)
		{
			tmp = p->map[i];
			p->map[i] = ft_realloc_mod(p->map[i], p->line, ' ');
			if (tmp != NULL && tmp != p->map[i])
				free (tmp);
			if (p->map[i] == NULL)
				ft_error("Error: malloc error!", p);
		}
		i++;
	}
}
