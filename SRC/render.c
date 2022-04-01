/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:34 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:35 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *draw, int x, int y, unsigned int color)
{
	char	*dst;

	dst = draw->addr + (y * draw->l_len + x * (draw->bpp / 8));
	*(unsigned *)dst = color;
}

unsigned int	get_pixel(t_img *img, unsigned x, unsigned y)
{
	return (*(unsigned *)(img->addr + (y * img->l_len + x * (img->bpp / 8))));
}

int	render(t_game *game)
{
	if (game->cnt_frame % 4 == 0)
	{
		mlx_clear_window(game->mlx, game->win);
		ft_cast_rays(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx, game->win, game->draw->img, 0, 0);
	}
	game->cnt_frame++;
	return (0);
}
