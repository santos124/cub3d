/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:56:00 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/02 23:56:02 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	player_look(int i, int j, t_parser *p)
{
	p->x = j + 0.5;
	p->y = i + 0.5;
	if (p->map[i][j] == 'S')
		p->angle = M_PI / 2;
	if (p->map[i][j] == 'N')
		p->angle = 3 * M_PI / 2;
	if (p->map[i][j] == 'E')
		p->angle = M_PI;
	if (p->map[i][j] == 'W')
		p->angle = 0;
}

void	parse_player(t_parser *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'E' || p->map[i][j] == 'W'
				|| p->map[i][j] == 'S' || p->map[i][j] == 'N')
			{
				player_look(i, j, p);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error("Error: no player on the map!", p);
}
