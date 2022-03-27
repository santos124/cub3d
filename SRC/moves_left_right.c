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

void	rot_left(t_game *game)
{
	game->plr->angle -= ROTATE_ANGLE;
	if (game->plr->angle < M_PI * 0.0)
		game->plr->angle = 2 * M_PI + game->plr->angle; 
	// printf("LEFT angle%f\n", game->plr->angle * 180 / M_PI);
}

void	rot_right(t_game *game)
{
	game->plr->angle += ROTATE_ANGLE;
	if (game->plr->angle > M_PI * 2)
		game->plr->angle = 2 * M_PI - game->plr->angle; 
	// printf("RIGHT 2 angle%f\n", game->plr->angle * 180 / M_PI);
}