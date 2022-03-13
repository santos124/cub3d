/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:01:46 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:01:48 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_game	*init_mem(char **av)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		game_close(3, game);
	*game = (t_game){0};
	game->space = ft_calloc(sizeof(t_img), 1);
	check_pointer(game->space, 3, game);
	game->wall = ft_calloc(sizeof(t_img), 1);
	check_pointer(game->wall, 3, game);
	game->tank = ft_calloc(sizeof(t_img *), 9);
	check_pointer(game->tank, 3, game);
	game->fuel = ft_calloc(sizeof(t_img *), 12);
	check_pointer(game->fuel, 3, game);
	game->exit = ft_calloc(sizeof(t_img), 1);
	check_pointer(game->exit, 3, game);
	game->mine = ft_calloc(sizeof(t_img), 1);
	check_pointer(game->mine, 3, game);
	game->map_name = ft_strdup(av[1]);
	check_pointer(game->map_name, 3, game);
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		game_close(6, NULL);
	game = init_mem(av);
	read_map(game, av[1]);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->w * 100, game->h * 100,
			"so_long");
	init_imgs(game);
	mlx_hook(game->win, 2, 1L << 0, key, game);
	mlx_hook(game->win, 17, 1L << 2, button, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (0);
}
