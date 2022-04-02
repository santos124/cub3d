/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:05 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:07 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_img(t_img **imga, t_game *game, int i)
{
	t_img	*img;

	*imga = malloc(sizeof(t_img));
	img = *imga;
	if (!(*imga))
		game_close(3, game);
	img->img = mlx_xpm_file_to_image(game->mlx,
			game->parser->path_direction[i], &img->w, &img->h);
	if (img->img == NULL)
		game_close(1, game);
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->l_len,
			&img->end);
	if (img->addr == NULL)
		game_close(1, game);
}

static void	init_imgs(t_game *game)
{
	get_img(&game->north_wall, game, 0);
	get_img(&game->south_wall, game, 1);
	get_img(&game->west_wall, game, 3);
	get_img(&game->east_wall, game, 2);
}

static t_game	*init_mem(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		game_close(3, game);
	*game = (t_game){0};
	game->plr = malloc(sizeof(t_plr));
	if (!game->plr)
		game_close(3, game);
	*game->plr = (t_plr){0};
	game->draw = malloc(sizeof(t_img));
	if (!game->draw)
		game_close(3, game);
	*game->draw = (t_img){0};
	return (game);
}

static void	init_game_var(t_game *game)
{
	game->map = game->parser->map;
	game->fov = FOV * M_PI / 180.0;
	game->plr->angle = game->parser->angle;
	game->plr->x = game->parser->x;
	game->plr->y = game->parser->y;
	game->x_mouse_now = 0;
	game->y_mouse_now = 0;
	game->toogle_mouse = 0;
	game->parser->map[(int)game->plr->y][(int)game->plr->x] = '0';
	game->h = game->parser->col;
	game->w = game->parser->line;
	game->cnt_frame = 0;
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		game_close(6, NULL);
	game = init_mem();
	game->parser = parse_all(av[1]);
	game->mlx = mlx_init();
	get_colors(game);
	game->draw->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->draw->addr = mlx_get_data_addr(game->draw->img, &game->draw->bpp,
			&game->draw->l_len, &game->draw->end);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	init_imgs(game);
	init_game_var(game);
	mlx_hook(game->win, 2, 1L << 0, key, game);
	mlx_hook(game->win, 17, 1L << 2, button, game);
	mlx_mouse_hook(game->win, mouse_toogle, game);
	mlx_hook(game->win, 6, 1L << 2, mouse_move, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (0);
}
