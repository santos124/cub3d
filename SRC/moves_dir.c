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

int in_wall(t_game *game, float x ,float y)
{
	(void)game;
	(void)x;
	(void)y;

	float x_c;
	float y_c;
	float angle = 0.0;
	float radius = FOOT * 2;

	while (angle < M_PI + M_PI)
	{
		x_c = cos(angle) * radius;
		y_c = sin(angle) * radius;
		if (game->map[(int)(y + y_c)][(int)(x + x_c)] == '1')
		{
			printf("ang=%f, %c\n", angle, game->map[(int)(y + y_c)][(int)(x + x_c)]);
			return (1);
		}
		angle += M_PI / 32;
	}
	return (0);
}

void	dir_down(t_game *game)
{

	if (!in_wall(game, game->plr->x + cos(game->plr->angle + M_PI) * FOOT, game->plr->y))
	{
		game->plr->x += cos(game->plr->angle + M_PI) * FOOT;
	}
	if (!in_wall(game, game->plr->x, game->plr->y + sin(game->plr->angle + M_PI) * FOOT))
	{
		game->plr->y += sin(game->plr->angle + M_PI) * FOOT;
	}
}

void	dir_right(t_game *game)
{	
	if (!in_wall(game, game->plr->x + cos(game->plr->angle + M_PI_2) * FOOT, game->plr->y))
	{
		game->plr->x += cos(game->plr->angle + M_PI_2) * FOOT;
	}
	if (!in_wall(game, game->plr->x, game->plr->y + sin(game->plr->angle + M_PI_2) * FOOT))
	{
		game->plr->y += sin(game->plr->angle + M_PI_2) * FOOT;
	}
}

void	dir_left(t_game *game)
{	
	if (!in_wall(game, game->plr->x + cos(game->plr->angle - M_PI_2) * FOOT, game->plr->y))
	{
		game->plr->x += cos(game->plr->angle - M_PI_2) * FOOT;
	}
	if (!in_wall(game, game->plr->x, game->plr->y + sin(game->plr->angle - M_PI_2) * FOOT))
	{
		game->plr->y += sin(game->plr->angle - M_PI_2) * FOOT;
	}
}



void	dir_up(t_game *game)
{	
	if (!in_wall(game, game->plr->x + cos(game->plr->angle) * FOOT, game->plr->y))
	{
		game->plr->x += cos(game->plr->angle) * FOOT;
	}
	if (!in_wall(game, game->plr->x, game->plr->y + sin(game->plr->angle) * FOOT))
	{
		game->plr->y += sin(game->plr->angle) * FOOT;
	}
}