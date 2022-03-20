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

#include "so_long.h"

static void	put_pixel(t_img *draw, int x, int y, unsigned color)
{
	char	*dst;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = draw->addr + (y * draw->l_len + x * (draw->bpp / 8));
		*(unsigned *)dst = color;
	}

}

static unsigned get_pixel(t_img *img, unsigned x, unsigned y)
{
	return (*(unsigned *)(img->addr + (y * img->l_len + x * (img->bpp / 8))));
}

static void ft_draw_ray(t_game *game, int x, float range, float angle)
{
	int y;
	int	h = HEIGHT / (range * cos(angle)); //пиксели по лучу
	y = 0; //старт координата текущего пикселя

	while (y < HEIGHT)
	{
		if (y > (HEIGHT - h) / 2 && y < HEIGHT - ((HEIGHT - h) / 2) && game->side_img)
		{
			put_pixel(game->draw, x, y, get_pixel(game->side_img, 
			game->x_side * game->north_wall->w,  512 * (y - (HEIGHT - h) / 2) / h));

		}
		else if (y < HEIGHT / 2)
			put_pixel(game->draw, x, y, 0x0087CEEB);
		else
			put_pixel(game->draw, x, y, 0x00FA8072);
		y++;
	}

}

static t_img *get_side_cub(t_game *game, t_plr *ray)
{
	if (game->map[(int)(ray->y)][(int)(ray->x + 0.01)] != '1')
	{
		
		game->x_side = ((float)(int)ray->y + 1.0000) - ray->y;
		// printf(" 1 plr->x=%f, plr->y=%f, ray->x=%f, ray->y=%f, ray->start=%f\n", game->plr->x, game->plr->y, ray->x, ray->y, ray->start);
		return game->east_wall;
	}
	if (game->map[(int)(ray->y + 0.01)][(int)(ray->x)] != '1')
	{
		game->x_side = ray->x - (float)(int)ray->x;
		// printf(" 2 plr->x=%f, plr->y=%f, ray->x=%f, ray->y=%f, ray->start=%f\n", game->plr->x, game->plr->y, ray->x, ray->y, ray->start);

		return game->south_wall;
	}
	if (game->map[(int)(ray->y)][(int)(ray->x - 0.01)] != '1')
	{
		game->x_side = ray->y - (float)(int)ray->y;
		// printf(" 3 plr->x=%f, plr->y=%f, ray->x=%f, ray->y=%f, ray->start=%f\n", game->plr->x, game->plr->y, ray->x, ray->y, ray->start);

		return game->west_wall;
	}
	if (game->map[(int)(ray->y - 0.01)][(int)(ray->x)] != '1')
	{

		game->x_side = ((float)(int)ray->x + 1.0000) - ray->x;
		// printf(" 4 plr->x=%f, plr->y=%f, ray->x=%f, ray->y=%f, ray->start=%f\n", game->plr->x, game->plr->y, ray->x, ray->y, ray->start);

		return game->north_wall;
	}

	return NULL;
}

static void	ft_cast_rays(t_game *game)
{
	t_plr	ray = *game->plr; // задаем координаты и направление луча равные координатам игрока
	ray.start = ray.angle - game->fov / 2.00; // начало веера лучей
	ray.end = ray.angle + game->fov / 2.00; // край веера лучей
	int d_x = 0;
	

	while (ray.start <= ray.end)
	{

		ray.x = game->plr->x; // каждый раз возвращаемся в точку начала
		ray.y = game->plr->y;
		while (game->map[(int)(ray.y)][(int)(ray.x)] != '1')
		{
			ray.x += cos(ray.start) / 100.0;
			ray.y += sin(ray.start) / 100.0;
		}
		game->side_img = get_side_cub(game, &ray);
		
		float range = sqrt(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.0));
		// if (game->side_img)
			ft_draw_ray(game, d_x, range, ray.start - game->plr->angle);
		d_x++;
		ray.start += game->fov / (float)WIDTH;
	}
	
}

// static void	ft_cast_ray(t_game *game)
// {
// 	t_plr	ray = *game->plr; // задаем координаты луча равные координатам игрока
// 	printf("start [%f][%f]=|%c|\n", ray.y, ray.x, game->map[(int)ray.y][(int)ray.x]);

// 	while (game->map[(int)ray.y][(int)ray.x] != '1' && ray.x < game->w)
// 	{
// 		ray.x += cos(ray.angle);
// 		ray.y -= sin(ray.angle);
// 		printf("loop [%f][%f]=|%c|\n", ray.y, ray.x, game->map[(int)ray.y][(int)ray.x]);
	
		
// 	}
// 	float range = sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.0));
// 	printf("end[%f][%f]=|%c|, range=%f| angle=%f| powf=%f, sqrtf=%f, rand1=%f, rand2=%f\n", ray.y, ray.x, \
// 		game->map[(int)ray.y][(int)ray.x], range, game->plr->angle, \
// 		powf(ray.x - game->plr->x, 2.0), \
// 		sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.00)), \
// 		powf(ray.x - game->plr->x, 2.0), powf(ray.y - game->plr->y, 2.00));
// 		// exit(0);
	
// 	ft_draw_ray(game, 200);
// }

int	render(t_game *game)
{

	game->plr->x = game->p_x + 0.5;
	game->plr->y = game->p_y + 0.5;
	game->fov = 66 * M_PI / 180.0;
	game->plr->angle = M_PI * 3  / 2.0;
	mlx_clear_window(game->mlx, game->win);
	

	
	ft_cast_rays(game);


	mlx_put_image_to_window(game->mlx, game->win, game->draw->img, 0, 0);


	// game_close(0, game);	
	return (0);
}
