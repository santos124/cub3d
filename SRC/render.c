/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:34 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:35 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->l_len + x * (game->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ft_cast_ray(t_game *game)
{
	t_plr	ray = *game->plr; // задаем координаты луча равные координатам игрока

	printf("window[%f][%f]=|%c|\n", game->plr->y, game->plr->x, game->map[(int)game->plr->y][(int)game->plr->x]);

	while (game->map[(int)game->plr->y][(int)game->plr->x] != '1' && ray.x < game->w)
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		printf("window[%f][%f]=%x\n", ray.y, ray.x, 0x00FF0000);
		my_pixel_put(game, ray.x, ray.y, 0x00FF0000);
	}
}

int	render(t_game *game)
{
	ft_cast_ray(game);
	sleep(3);
	game_close(0, game);	
	return (0);
}
