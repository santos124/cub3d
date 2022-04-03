/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 00:00:53 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/03 00:00:57 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_valid_char(t_parser *p)
{
	int	i;
	int	j;
	int	dup;

	dup = 0;
	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] != 'N' && p->map[i][j] != 'S' &&
				p->map[i][j] != 'W' && p->map[i][j] != 'E' &&
				p->map[i][j] != '1' && p->map[i][j] != '0' &&
				p->map[i][j] != ' ')
				return (ft_error("Error: invalid characters detected!", p));
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S' ||
				p->map[i][j] == 'W' || p->map[i][j] == 'E')
				dup++;
			if (dup > 1)
				return (ft_error("Error: repeatable characters detected!", p));
			j++;
		}
		i++;
	}
}

static void	ft_sub_super_malloc(char **map, int *j, int *i, char **new)
{
	if (map[*i])
	{
		new[*i] = ft_strdup(map[*i]);
		*j = *i;
		if (!new[*i])
			ft_error("Error: malloc error!", NULL);
	}
	else
		new[*i] = NULL;
	(*i)++;
}

char	**ft_super_malloc(char **map, int num)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (num + 1));
	if (new == NULL)
		ft_error("Error: malloc error!", NULL);
	while (i < num)
		ft_sub_super_malloc(map, &j, &i, new);
	new[i] = NULL;
	while (j >= 0)
		free(map[j--]);
	free(map);
	return (new);
}

void	check_map_format(char *file, int *fd)
{
	int	num;

	num = ft_strlen(file);
	if (ft_strncmp(file + num - 4, ".cub", 4) || num < 5
		|| read(*fd, 0, 0) < 0)
		ft_error("Error: incorrect map format!", NULL);
	if (*fd == -1)
		ft_error("Error: mapfile not detected!", NULL);
}
