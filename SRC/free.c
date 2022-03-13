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

#include "so_long.h"

static void	liberty(void **pointer)
{
	if (!(*pointer))
	{
		free(*pointer);
		*pointer = NULL;
	}
}

static void	clear_img(t_img **pic, t_game *game)
{
	if (*pic)
	{
		if ((*pic)->img && game->mlx)
			mlx_destroy_image(game->mlx, (*pic)->img);
		free(*pic);
		*pic = NULL;
	}
}

void	liberator(t_game	*game)
{
	int	y;

	y = -1;
	if (game->map_name)
		liberty((void **)&game->map_name);
	while (game->map[++y])
	{
		if (game->map[y])
			liberty((void **)&game->map[y]);
	}
	clear_img(&game->space, game);
	clear_img(&game->wall, game);
	clear_img(&game->food, game);
	clear_img(&game->exit, game);
	clear_img(&game->pers, game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
}
