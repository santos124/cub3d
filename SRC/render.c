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

static void	my_pixel_put(t_img *draw, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = draw->addr + (y * draw->l_len + x * (draw->bpp / 8));
		*(unsigned int*)dst = color;
	}

}

// static void ft_draw_ray(t_game *game, int x, float range)
// {

// 	int i = 0;
// 	int mid = HEIGHT / 2;
// 	int y;
// 	while (i + mid < HEIGHT)
// 	{
// 		y = mid + (i / range);
// 		// printf("243 XYU  |%d|%d|%d|%d|%f|%f\n", HEIGHT, x, y, mid, range, game->plr->angle );
// 		my_pixel_put(game->draw, x, y, 0x0000FF00 / range);
// 		y = mid - (i / range);
// 		my_pixel_put(game->draw, x, y, 0x00FF0000 / range);
// 		i++;
// 	}


// }

static void ft_draw_ray(t_game *game, int x, float range, float angle)
{
	int y;
	int	h = HEIGHT / (range * cosf(angle)); //пиксели по лучу
	y = 0; //старт координата текущего пикселя


	while (y < HEIGHT)
	{
		if (y > (HEIGHT - h) / 2 && y < HEIGHT - ((HEIGHT - h) / 2))
			my_pixel_put(game->draw, x, y, 0x0000FF00 / range);
		else if (y < HEIGHT / 2)
			my_pixel_put(game->draw, x, y, 0x0087CEEB);
		else
			my_pixel_put(game->draw, x, y, 0x00FA8072);
		y++;
	}

}

void	ft_cast_rays(t_game *game)
{
	t_plr	ray = *game->plr; // задаем координаты и направление луча равные координатам игрока
	ray.start = ray.angle - game->fov / 2; // начало веера лучей
	ray.end = ray.angle + game->fov / 2; // край веера лучей
	int d_x = 0;

	while (ray.start <= ray.end)
	{

		ray.x = game->plr->x + 0.5; // каждый раз возвращаемся в точку начала
		ray.y = game->plr->y + 0.5;
		while (game->map[(int)(ray.y)][(int)(ray.x)] != '1')
		{
			ray.x += cos(ray.start) / 100.0f;
			ray.y += sin(ray.start) / 100.0f;
			// printf("XYU 2 \n");
		}

		float range = sqrt(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.0));
		// printf("243 XYU  %f|%f\n", range, game->plr->angle );

		// printf("XYU [%f][%f]=|%c|, range=%f| angle=%f| powf=%f, sqrtf=%f, rand1=%f, rand2=%f\n", ray.y, ray.x, \
		// game->map[(int)ray.y][(int)ray.x], range, ray.start, \
		// powf(ray.x - game->plr->x, 2.0), \
		// sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.00)), \
		// powf(ray.x - game->plr->x, 2.0), powf(ray.y - game->plr->y, 2.00));
	
		ft_draw_ray(game, d_x, range, game->fov - ray.start);
		d_x++;
		ray.start += game->fov / WIDTH;
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


	game->fov = M_PI /2;
	game->plr->angle = M_PI  / 2;
	mlx_clear_window(game->mlx, game->win);
	

	
	ft_cast_rays(game);


	mlx_put_image_to_window(game->mlx, game->win, game->draw->img, 0, 0);


	// game_close(0, game);	
	return (0);
}
