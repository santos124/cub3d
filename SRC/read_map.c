/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:25 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:27 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	pers_find(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == 'P')
			{
				game->p_y = y;
				game->p_x = x;
			}
			x++;
		}
		y++;
	}
	game->plr->x = (float)game->p_x + 0.5;
	game->plr->y = (float)game->p_y + 0.5;
}

static void	valid_map_continue(t_game *game)
{
	int	x;
	int	y;

	y = 0;
//	if (game->exit_cnt == 0 || game->food_cnt == 0 || game->pers_cnt != 1)
//		game_close(4, game);
	x = 0;
	while (x < game->w)
	{
		if (game->map[0][x] != '1' || game->map[game->h - 1][x] != '1')
			game_close(4, game);
		x++;
	}
	y = 0;
	while (y < game->h)
	{
		if (game->map[y][0] != '1' || game->map[y][game->w - 1] != '1')
			game_close(4, game);
		y++;
	}
}

static void	valid_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
//			if (ft_strlen(game->map[y]) != (size_t)game->w || (game->map[y][x]
//				!= '1' && game->map[y][x] != '0' && game->map[y][x] != 'C' &&
//				game->map[y][x] != 'P' && game->map[y][x] != 'E'))
//				game_close(4, game);
//			if (game->map[y][x] == 'P')
//				game->pers_cnt++;
//			if (game->map[y][x] == 'C')
//				game->food_cnt++;
//			if (game->map[y][x] == 'E')
//				game->exit_cnt++;
			x++;
		}
		y++;
	}
	valid_map_continue(game);
}

static void	memories(char ***old_map, t_game *game, int *i, char **line)
{
	game->h++;
	*old_map = game->map;
	game->map = (char **)ft_calloc(sizeof(char *), game->h + 1);
	if (!game->map)
		game_close(3, game);
	while ((*old_map)[++*i])
		game->map[*i] = (*old_map)[*i];
	game->map[*i] = *line;
	game->map[*i + 1] = NULL;
	*i = -1;
	free(*old_map);
}

void	read_map(t_game *game, char *map_name)
{
	int		fd;
	int		ret;
	char	*line;
	char	**old_map;
	int		i;

	i = -1;
	ret = 1;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		game_close(6, game);
	game->map = (char **)ft_calloc(sizeof(char *), 1);
	if (!game->map)
		game_close(3, game);
	while (ret > 0)
	{
		ret = gnl(fd, &line);
		if (ret == -1)
			game_close(2, game);
		memories(&old_map, game, &i, &line);
	}
	close(fd);
	game->w = ft_strlen(game->map[0]);
	valid_map(game);
	pers_find(game);
}
