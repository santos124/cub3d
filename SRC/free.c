/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:59:57 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 01:59:59 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	liberty(void **pointer)
{
	if (!(*pointer))
	{
		free(*pointer);
		*pointer = NULL;
	}
}

void	liberator(t_game	*game)
{
	int	y;

	y = -1;
	while (game->map[++y])
	{
		if (game->map[y])
			liberty((void **)&game->map[y]);
	}
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
}
