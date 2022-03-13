/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:02:01 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:02:02 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
}

static void	enemy_init(t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	y = -1;
	game->mines = ft_calloc(game->enemy_cnt + 1, sizeof(t_enemy *));
	if (!game->mines)
		game_close(3, game);
	while (++y < game->h)
	{
		x = -1;
		while (++x < game->w)
		{
			if (game->map[y][x] == 'X')
			{
				game->mines[++i] = ft_calloc(1, sizeof(t_enemy));
				if (!game->mines[i])
					game_close(3, game);
				game->mines[i]->d = 0;
				game->mines[i]->x = x;
				game->mines[i]->y = y;
			}
		}
	}
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
	check_pointer(game->map, 3, game);
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
	enemy_init(game);
}
