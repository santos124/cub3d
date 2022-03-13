/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:30:57 by wadina            #+#    #+#             */
/*   Updated: 2022/01/03 18:30:58 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	valid_map_continue(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	if (game->exit_cnt == 0 || game->food_cnt == 0 || game->pers_cnt != 1)
		game_close(4, game);
	x = 0;
	while (x < game->w)
	{
		if (game->map[0][x] != '1' || game->map[game->h - 1][x] != '1')
			game_close(4, game);
		x++;
	}
	y = 0;
	while (y < game->h)
	{
		if (game->map[y][0] != '1' || game->map[y][game->w - 1] != '1')
			game_close(4, game);
		y++;
	}
}

void	valid_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->h)
	{
		x = -1;
		while (++x < game->w)
		{
			if (ft_strlen(game->map[y]) != (size_t)game->w || (game->map[y][x]
				!= '1' && game->map[y][x] != '0' && game->map[y][x] != 'C' &&
			game->map[y][x] != 'P' && game->map[y][x] != 'E' &&
			game->map[y][x] != 'X'))
				game_close(4, game);
			if (game->map[y][x] == 'P')
				game->pers_cnt++;
			if (game->map[y][x] == 'C')
				game->food_cnt++;
			if (game->map[y][x] == 'E')
				game->exit_cnt++;
			if (game->map[y][x] == 'X')
				game->enemy_cnt++;
		}
	}
	valid_map_continue(game);
}
