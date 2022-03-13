/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 01:59:44 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 01:59:50 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_close(int err, t_game *game)
{
	if (err == 6)
	{
		ft_putendl_fd("Error\nNeed map name", 2);
		exit(6);
	}
	liberator(game);
	if (err == 1)
		ft_putendl_fd("Error\nOpen error", 2);
	else if (err == 2)
		ft_putendl_fd("Error\nRead error", 2);
	else if (err == 3)
		ft_putendl_fd("Error\nMalloc error", 2);
	else if (err == 4)
		ft_putendl_fd("Error\nValid map error", 2);
	else if (err == 5)
		ft_putendl_fd("Game interupted of ESC", 1);
	else if (err == 0)
		ft_putendl_fd("Game done", 1);
	if (err == 8)
		ft_putendl_fd("Game closed by red crosshair", 1);
	exit(err);
}

int	button(t_game *game)
{
	game_close(8, game);
	return (0);
}
