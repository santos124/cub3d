/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 02:40:03 by wadina            #+#    #+#             */
/*   Updated: 2022/03/31 02:40:04 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_side_cub(t_game *game, t_plr *ray)
{
	if (game->map[(int)(ray->y)][(int)(ray->x + 0.01)] == '0')
	{
		game->x_side = ((long double)(int)ray->y + 1.0000) - ray->y;
		return (game->west_wall);
	}
	if (game->map[(int)(ray->y + 0.01)][(int)(ray->x)] == '0')
	{
		game->x_side = ray->x - (long double)(int)ray->x;
		return (game->north_wall);
	}
	if (game->map[(int)(ray->y)][(int)(ray->x - 0.01)] == '0')
	{
		game->x_side = ray->y - (long double)(int)ray->y;
		return (game->east_wall);
	}
	if (game->map[(int)(ray->y - 0.01)][(int)(ray->x)] == '0')
	{
		game->x_side = ((long double)(int)ray->x + 1.0000) - ray->x;
		return (game->south_wall);
	}
	game->x_side = 0;
	return (game->east_wall);
}

static void	ft_draw_ray(t_game *game, int x, t_plr ray)
{
	int				y;
	float			h;
	long double		range;

	game->side_img = get_side_cub(game, &game->ray);
	range = sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y,
				2.0));
	h = (float)HEIGHT / (range * cosf(game->plr->angle - ray.start));
	y = 0;
	while (y < HEIGHT)
	{
		if (y > (HEIGHT - h) / 2 && y < HEIGHT - ((HEIGHT - h) / 2)
			&& game->side_img)
		{
			put_pixel(game->draw, x, y, get_pixel(game->side_img,
					game->x_side * game->north_wall->w, game->side_img->h
					* (y - (HEIGHT - h) / 2) / h));
		}
		else if (y < HEIGHT / 2)
			put_pixel(game->draw, x, y, game->color_top);
		else
			put_pixel(game->draw, x, y, game->color_bot);
		y++;
	}
}

static void	get_end_ray_pos(t_game *game)
{
	while (game->map[(int)(game->ray.y)][(int)(game->ray.x)] == '0')
	{
		game->ray.x += game->cosinus / 100.0;
		game->ray.y += game->sinus / 100.0;
	}
}

void	ft_cast_rays(t_game *game)
{
	game->speed = 1.0 / (long double)WIDTH;
	game->accel = 2.0 * (game->fov / 2.0 - game->speed * WIDTH / 2)
		/ ((WIDTH / 2) * (WIDTH / 2));
	game->ray = *game->plr;
	game->ray.start = game->ray.angle - game->fov / 2.00;
	game->ray.end = game->ray.angle + game->fov / 2.00;
	game->d_x = 0;
	while (game->d_x < WIDTH)
	{
		if (game->ray.start <= game->ray.angle)
			game->speed += game->accel;
		else
			game->speed -= game->accel;
		game->ray.start += game->speed;
		game->ray.x = game->plr->x;
		game->ray.y = game->plr->y;
		game->cosinus = cos(game->ray.start);
		game->sinus = sin(game->ray.start);
		get_end_ray_pos(game);
		ft_draw_ray(game, game->d_x++, game->ray);
	}
}
