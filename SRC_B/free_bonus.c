/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:01:39 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:01:41 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

static void	clear_imgs(t_img ***pic, t_game *game)
{
	int	i;

	i = 0;
	while ((*pic)[i])
	{
		clear_img(&(*pic)[i], game);
		i++;
	}
	free(*pic);
	*pic = NULL;
}

static void	clear_enemies(t_game	*game)
{
	int	i;

	i = 0;
	if (game->mines)
	{
		while (game->mines[i])
		{
			free(game->mines[i]);
			game->mines[i++] = NULL;
		}
	}
}

void	liberator(t_game	*game)
{
	int	y;

	y = -1;
	if (game->map_name)
		liberty((void **)&game->map_name);
	while (game->map[++y])
		if (game->map[y])
			liberty((void **)&game->map[y]);
	clear_imgs(&game->tank, game);
	clear_imgs(&game->fuel, game);
	clear_img(&game->space, game);
	clear_img(&game->wall, game);
	clear_img(&game->exit, game);
	clear_img(&game->mine, game);
	clear_enemies(game);
	if (game->mlx != NULL && game->win != NULL)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
}
