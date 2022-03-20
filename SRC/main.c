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

#include "so_long.h"

static void	init_imgs(t_game *game)
{
//	game->pers->img = mlx_xpm_file_to_image(game->mlx, "imgs/persM.xpm",
//			&game->pers->w, &game->pers->h);
//	if (game->pers->img == NULL)
//		game_close(1, game);
//	game->space->img = mlx_xpm_file_to_image(game->mlx, "imgs/spaceM.xpm",
//			&game->space->w, &game->space->h);
//	if (game->space->img == NULL)
//		game_close(1, game);
//	game->wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/wallM.xpm",
//			&game->wall->w, &game->wall->h);
//	if (game->wall->img == NULL)
//		game_close(1, game);
//	game->food->img = mlx_xpm_file_to_image(game->mlx, "imgs/foodM.xpm",
//			&game->food->w, &game->food->h);
//	if (game->wall->img == NULL)
//		game_close(1, game);
//	game->exit->img = mlx_xpm_file_to_image(game->mlx, "imgs/exitM.xpm",
//			&game->exit->w, &game->exit->h);
//	if (game->exit->img == NULL)
//		game_close(1, game);
	//t_img выше которые, все удалить
	game->north_wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/north.xpm",
			&game->north_wall->w, &game->north_wall->h);
	if (game->north_wall->img == NULL)
		game_close(1, game);
	game->north_wall->addr = mlx_get_data_addr(game->north_wall->img, &game->north_wall->bpp, &game->north_wall->l_len, &game->north_wall->end);
	if (game->north_wall->addr == NULL)
		game_close(1, game);

	//остальыне также взять addr и проверку на маллок
	game->west_wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/west.xpm",
			&game->west_wall->w, &game->west_wall->h);
	if (game->west_wall->img == NULL)
		game_close(1, game);
	game->south_wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/south.xpm",
			&game->south_wall->w, &game->south_wall->h);
	if (game->south_wall->img == NULL)
		game_close(1, game);
	game->east_wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/east.xpm",
			&game->east_wall->w, &game->east_wall->h);
	if (game->east_wall->img == NULL)
		game_close(1, game);
	
}

static void	init_game(t_game *game)
{
	*game = (t_game){0};
}

static t_game	*init_mem(char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		game_close(3, game);
	init_game(game);
//	game->space = malloc(sizeof(t_img));
//	if (!game->space)
//		game_close(3, game);
//	game->wall = malloc(sizeof(t_img));
//	if (!game->wall)
//		game_close(3, game);
//	game->food = malloc(sizeof(t_img));
//	if (!game->food)
//		game_close(3, game);
//	game->exit = malloc(sizeof(t_img));
//	if (!game->exit)
//		game_close(3, game);
//	game->pers = malloc(sizeof(t_img));
//	if (!game->pers)
//		game_close(3, game);
	game->map_name = ft_strdup(av[1]);
	if (!game->map_name)
		game_close(3, game);
	game->plr = malloc(sizeof(t_plr));
	if (!game->plr)
		game_close(3, game);
	*game->plr = (t_plr){0};
	game->draw = malloc(sizeof(t_img));
	if (!game->draw)
		game_close(3, game);
	*game->draw = (t_img){0};

	game->north_wall = malloc(sizeof(t_img));
	if (!game->north_wall)
		game_close(3, game);
	game->west_wall = malloc(sizeof(t_img));
	if (!game->west_wall)
		game_close(3, game);
	game->south_wall = malloc(sizeof(t_img));
	if (!game->south_wall)
		game_close(3, game);
	game->east_wall = malloc(sizeof(t_img));
	if (!game->east_wall)
		game_close(3, game);
	
	

	return (game);
}

void print_map(t_game *game)
{
	int y = 0;
	while (y < game->h)
	{
		printf("s[%d]=%s\n", y, game->map[y]);
		y++;
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	
	if (ac != 2)
		game_close(6, NULL);
	
		
	game = init_mem(av);
	printf("PRIVET\n");
	read_map(game, av[1]);
	print_map(game);
	game->mlx = mlx_init();
	game->draw->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);

	game->draw->addr = mlx_get_data_addr(game->draw->img, &game->draw->bpp, &game->draw->l_len,
								&game->draw->end);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "so_long");
	
	init_imgs(game);
	mlx_hook(game->win, 2, 1L << 0, key, game);
	mlx_hook(game->win, 17, 1L << 2, button, game);
	mlx_loop_hook(game->mlx, render, game);
	
	mlx_loop(game->mlx);
	return (0);
}

