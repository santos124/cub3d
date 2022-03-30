/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 02:39:55 by wadina            #+#    #+#             */
/*   Updated: 2022/03/31 02:39:57 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_men_map(t_game *game)
{
	int	i;
	int	j;

	i = -5;
	j = i;
	while (i < (HEIGHT / 70) / 4)
	{
		j = -5;
		while (j < (HEIGHT / 70) / 4)
		{
			put_pixel(game->draw, (game->plr->x) * (HEIGHT / 70) + j,
				(game->plr->y) * (HEIGHT / 70) + i, 0x000000FF);
			j++;
		}
		i++;
	}	
}

void	put_rectanlge_map(t_game *game, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (HEIGHT / 70))
	{
		j = 0;
		while (j < (HEIGHT / 70))
		{
			put_pixel(game->draw, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = x;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == '1')
				put_rectanlge_map(game, x * (HEIGHT / 70), y * (HEIGHT / 70),
					100);
			x++;
		}
		y++;
	}
	put_men_map(game);
}
