/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:11 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:13 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	dir_down(t_game *game)
{
	
	if (game->map[(int)(game->plr->y)][(int)(game->plr->x + cos(game->plr->angle + M_PI) * FOOT)] != '1')
	{
		game->plr->x += cos(game->plr->angle + M_PI) * FOOT;
	}
	if (game->map[(int)(game->plr->y + sin(game->plr->angle + M_PI) * FOOT)][(int)(game->plr->x)] != '1')
	{
		game->plr->y += sin(game->plr->angle + M_PI) * FOOT;
	}
}

void	dir_right(t_game *game)
{
	
	if (game->map[(int)(game->plr->y)][(int)(game->plr->x + cos(game->plr->angle + M_PI_2) * FOOT)] != '1')
	{
		game->plr->x += cos(game->plr->angle + M_PI_2) * FOOT;
	}
	if (game->map[(int)(game->plr->y + sin(game->plr->angle + M_PI_2) * FOOT)][(int)(game->plr->x)] != '1')
	{
		game->plr->y += sin(game->plr->angle + M_PI_2) * FOOT;
	}
}

void	dir_left(t_game *game)
{

	
	if (game->map[(int)(game->plr->y)][(int)(game->plr->x + cos(game->plr->angle - M_PI_2) * FOOT)] != '1')
	{
		game->plr->x += cos(game->plr->angle - M_PI_2) * FOOT;
	}
	if (game->map[(int)(game->plr->y + sin(game->plr->angle - M_PI_2) * FOOT)][(int)(game->plr->x)] != '1')
	{
		game->plr->y += sin(game->plr->angle - M_PI_2) * FOOT;
	}
}

void	dir_up(t_game *game)
{

	
	// printf("cell=%c\n", game->map[(int)(game->plr->x + cos(game->plr->angle) * FOOT)][(int)(game->plr->y + sin(game->plr->angle) * FOOT)]);
	if (game->map[(int)(game->plr->y)][(int)(game->plr->x + cos(game->plr->angle) * FOOT)] != '1')
	{
		game->plr->x += cos(game->plr->angle) * FOOT;
	}
	if (game->map[(int)(game->plr->y + sin(game->plr->angle) * FOOT)][(int)(game->plr->x)] != '1')
	{
		game->plr->y += sin(game->plr->angle) * FOOT;
	}

}