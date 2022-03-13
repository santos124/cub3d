/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:30:39 by wadina            #+#    #+#             */
/*   Updated: 2022/01/03 18:30:41 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	**get_names_tank(t_game	*game)
{
	char	**tanks;

	tanks = ft_calloc(sizeof(char *), 9);
	check_pointer(tanks, 3, game);
	tanks[0] = ft_strdup("imgs/tank00.xpm");
	check_pointer(tanks[0], 3, game);
	tanks[1] = ft_strdup("imgs/tank10.xpm");
	check_pointer(tanks[1], 3, game);
	tanks[2] = ft_strdup("imgs/tank20.xpm");
	check_pointer(tanks[2], 3, game);
	tanks[3] = ft_strdup("imgs/tank30.xpm");
	check_pointer(tanks[3], 3, game);
	tanks[4] = ft_strdup("imgs/tank01.xpm");
	check_pointer(tanks[4], 3, game);
	tanks[5] = ft_strdup("imgs/tank11.xpm");
	check_pointer(tanks[5], 3, game);
	tanks[6] = ft_strdup("imgs/tank21.xpm");
	check_pointer(tanks[6], 3, game);
	tanks[7] = ft_strdup("imgs/tank31.xpm");
	check_pointer(tanks[7], 3, game);
	return (tanks);
}

static void	get_tank(t_game *game)
{
	int		i;
	char	**s;

	s = get_names_tank(game);
	i = 0;
	while (i < 8)
	{
		game->tank[i] = (t_img *)ft_calloc(sizeof(t_img), 1);
		if (!game->tank[i])
			game_close(3, game);
		game->tank[i]->img = mlx_xpm_file_to_image(game->mlx, s[i],
				&game->tank[i]->width, &game->tank[i]->height);
		if (game->tank[i]->img == NULL)
			game_close(4, game);
		i++;
	}
	i = 0;
	while (i < 8)
		free(s[i++]);
	free(s);
}

static char	**get_names_fuel(t_game	*game)
{
	char	**fuels;

	fuels = ft_calloc(sizeof(char *), 9);
	check_pointer(fuels, 3, game);
	fuels[0] = ft_strdup("imgs/fuel1.xpm");
	check_pointer(fuels[0], 3, game);
	fuels[1] = ft_strdup("imgs/fuel2.xpm");
	check_pointer(fuels[1], 3, game);
	fuels[2] = ft_strdup("imgs/fuel3.xpm");
	check_pointer(fuels[2], 3, game);
	fuels[3] = ft_strdup("imgs/fuel4.xpm");
	check_pointer(fuels[3], 3, game);
	fuels[4] = ft_strdup("imgs/fuel5.xpm");
	check_pointer(fuels[4], 3, game);
	fuels[5] = ft_strdup("imgs/fuel6.xpm");
	check_pointer(fuels[5], 3, game);
	fuels[6] = ft_strdup("imgs/fuel7.xpm");
	check_pointer(fuels[6], 3, game);
	fuels[7] = ft_strdup("imgs/fuel8.xpm");
	check_pointer(fuels[7], 3, game);
	return (fuels);
}

static void	get_fuel(t_game *game)
{
	int		i;
	char	**s;

	s = get_names_fuel(game);
	i = 0;
	while (i < 8)
	{
		game->fuel[i] = (t_img *)ft_calloc(sizeof(t_img), 1);
		if (!game->fuel[i])
			game_close(3, game);
		game->fuel[i]->img = mlx_xpm_file_to_image(game->mlx, s[i],
				&game->fuel[i]->width, &game->fuel[i]->height);
		if (game->fuel[i]->img == NULL)
			game_close(4, game);
		i++;
	}
	i = 0;
	while (i < 8)
		free(s[i++]);
	free(s);
}

void	init_imgs(t_game *game)
{
	get_tank(game);
	get_fuel(game);
	game->space->img = mlx_xpm_file_to_image(game->mlx, "imgs/grass.xpm",
			&game->space->width, &game->space->height);
	check_pointer(game->space->img, 3, game);
	game->wall->img = mlx_xpm_file_to_image(game->mlx, "imgs/wall.xpm",
			&game->wall->width, &game->wall->height);
	check_pointer(game->wall->img, 3, game);
	game->mine->img = mlx_xpm_file_to_image(game->mlx, "imgs/mine.xpm",
			&game->mine->width, &game->mine->height);
	check_pointer(game->mine->img, 3, game);
	game->exit->img = mlx_xpm_file_to_image(game->mlx, "imgs/exit.xpm",
			&game->exit->width, &game->exit->height);
	check_pointer(game->exit->img, 3, game);
}
