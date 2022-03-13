/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:01:53 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:01:54 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	dir_left(t_game *game)
{
	game->p_d = 1;
	if (game->p_x > 0)
	{
		if (game->map[game->p_y][game->p_x - 1] == 'C')
		{
			game->eat_food++;
			game->food_cnt--;
			game->map[game->p_y][game->p_x - 1] = '0';
		}
		if (game->map[game->p_y][game->p_x - 1] != '1')
		{
			game->p_x--;
			game->did_move = 1;
		}
		else
		{
			game->did_move = 0;
			game->move_cnt--;
		}
	}
}

static void	dir_right(t_game *game)
{
	game->p_d = 3;
	if (game->p_x < game->w - 1)
	{
		if (game->map[game->p_y][game->p_x + 1] == 'C')
		{
			game->eat_food++;
			game->food_cnt--;
			game->map[game->p_y][game->p_x + 1] = '0';
		}
		if (game->map[game->p_y][game->p_x + 1] != '1')
		{
			game->p_x++;
			game->did_move = 1;
		}
		else
		{
			game->did_move = 0;
			game->move_cnt--;
		}
	}
}

static void	dir_down(t_game *game)
{
	game->p_d = 2;
	if (game->p_y < game->h - 1)
	{
		if (game->map[game->p_y + 1][game->p_x] == 'C')
		{
			game->eat_food++;
			game->food_cnt--;
			game->map[game->p_y + 1][game->p_x] = '0';
		}
		if (game->map[game->p_y + 1][game->p_x] != '1')
		{
			game->p_y++;
			game->did_move = 1;
		}
		else
		{
			game->did_move = 0;
			game->move_cnt--;
		}
	}
}

static void	dir_up(t_game *game)
{
	game->p_d = 0;
	if (game->p_y > 0)
	{
		if (game->map[game->p_y - 1][game->p_x] == 'C')
		{
			game->eat_food++;
			game->food_cnt--;
			game->map[game->p_y - 1][game->p_x] = '0';
		}
		if (game->map[game->p_y - 1][game->p_x] != '1')
		{
			game->p_y--;
			game->did_move = 1;
		}
		else
		{
			game->did_move = 0;
			game->move_cnt--;
		}
	}
}

int	key(int keycode, t_game *game)
{
	game->move_cnt++;
	game->eat_food = 0;
	if (keycode == 53)
		game_close(5, game);
	else if (keycode == 0)
		dir_left(game);
	else if (keycode == 1)
		dir_down(game);
	else if (keycode == 2)
		dir_right(game);
	else if (keycode == 13)
		dir_up(game);
	else
		return (0);
	if (game->food_cnt == 0 && game->map[game->p_y][game->p_x] == 'E')
		game_close(0, game);
	return (0);
}
