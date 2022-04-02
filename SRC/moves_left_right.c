/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_left_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 02:44:06 by wadina            #+#    #+#             */
/*   Updated: 2022/03/31 02:44:07 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left_m(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->plr->angle -= ROTATE_ANGLE / 10;
		if (game->plr->angle < M_PI * 2 * (-10))
			game->plr->angle = 2 * M_PI + game->plr->angle;
		i++;
	}
}

void	rot_right_m(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->plr->angle += ROTATE_ANGLE / 10;
		if (game->plr->angle > M_PI * 2 * 10)
			game->plr->angle = 2 * M_PI - game->plr->angle;
		i++;
	}
}

void	rot_left(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->plr->angle -= ROTATE_ANGLE / 5;
		if (game->plr->angle < M_PI * 2 * (-10))
			game->plr->angle = 2 * M_PI + game->plr->angle;
		i++;
	}
}

void	rot_right(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->plr->angle += ROTATE_ANGLE / 5;
		if (game->plr->angle > M_PI * 2 * 10)
			game->plr->angle = 2 * M_PI - game->plr->angle;
		i++;
	}
}
