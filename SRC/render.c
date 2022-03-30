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

void	put_pixel(t_img *draw, int x, int y, unsigned color)
{
	char	*dst;
	// if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	// {
		dst = draw->addr + (y * draw->l_len + x * (draw->bpp / 8));
		*(unsigned *)dst = color;
	// }

}

static unsigned get_pixel(t_img *img, unsigned x, unsigned y)
{

	return (*(unsigned *)(img->addr + (y * img->l_len + x * (img->bpp / 8))));
}





static t_img *get_side_cub(t_game *game, t_plr *ray)
{
	if (game->map[(int)(ray->y)][(int)(ray->x + 0.01)] != '1')
	{
		game->x_side = ((long double)(int)ray->y + 1.0000) - ray->y;
		return game->east_wall;
	}
	if (game->map[(int)(ray->y + 0.01)][(int)(ray->x)] != '1')
	{
		game->x_side = ray->x - (long double)(int)ray->x;
		return game->south_wall;
	}
	if (game->map[(int)(ray->y)][(int)(ray->x - 0.01)] != '1')
	{
		game->x_side = ray->y - (long double)(int)ray->y;
		return game->west_wall;
	}
	if (game->map[(int)(ray->y - 0.01)][(int)(ray->x)] != '1')
	{
		game->x_side = ((long double)(int)ray->x + 1.0000) - ray->x;
		return game->north_wall;
	}
	game->x_side = 0;
	return game->east_wall;
}

static void ft_draw_ray(t_game *game, int x, long double range, long double angle)
{
	int y;
	(void)angle;
	long double	h = (long double)HEIGHT / (range * cosf(angle) ); //высота в пикселях столбца стены
	y = 0; //старт координата текущего пикселя

	while (y < HEIGHT)
	{
		if (y > (HEIGHT - h) / 2 && y < HEIGHT - ((HEIGHT - h) / 2) && game->side_img) //проверка на то что пиксель находится в сегменте столбца который относится к стене а не к потолкку и полу
		{
			put_pixel(game->draw, x, y, get_pixel(game->side_img, 
			game->x_side * game->north_wall->w,  game->side_img->h * (y - (HEIGHT - h) / 2) / h)); //отправить пиксель в ИМГ

		}
		else if (y < HEIGHT / 2) //рисовать потолок
			put_pixel(game->draw, x, y, 0x00A99B98);
		else//рисовать пол
			put_pixel(game->draw, x, y, 0x00473E3D);
		y++; //опускаемся на следующий пиксель
	}

}


// static void	ft_cast_rays(t_game *game)
// {
// 	t_plr	ray = *game->plr;// задаем координаты и направление луча равные координатам игрока
// 	ray.start = ray.angle - game->fov / 2.00;// начало веера лучей
// 	ray.end = ray.angle + game->fov / 2.00;// край веера лучей
// 	int d_x = 0;
// 	long double cosinus;
// 	long double sinus;
// 	while (d_x < WIDTH)
// 	{
// 		ray.x = game->plr->x;// каждый раз возвращаемся в точку начала
// 		ray.y = game->plr->y;
// 		cosinus = cos(ray.start);
// 		sinus = sin(ray.start);
// 		while (game->map[(int)(ray.y)][(int)(ray.x)] != '1')//пока не воткну луч в стену
// 		{
// 			ray.x += cosinus / 100.0;
// 			ray.y += sinus / 100.0;
// 			put_pixel(game->minimap, (ray.x) * game->k_map, (ray.y) * game->k_map, 0x5500EE00);
// 		}
// 		game->side_img = get_side_cub(game, &ray);//получаю указатель на одну из структур изображений
// 		long double range = sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.0)); //длина луча грязная
// 		ft_draw_ray(game, d_x, range,  game->plr->angle - ray.start); //рисовать столбец полностью с полом и потолком
// 		d_x++;//переход на след столбец камеры
// 		ray.start += game->fov / WIDTH; //переход луча на след угол
		

// 	}
// }

static void	ft_cast_rays(t_game *game)
{
	t_plr	ray = *game->plr;// задаем координаты и направление луча равные координатам игрока
	ray.start = ray.angle - game->fov / 2.00;// начало веера лучей
	ray.end = ray.angle + game->fov / 2.00;// край веера лучей
	int d_x = 0;
	long double cosinus;
	long double sinus;
	long double speed = 1.0 / (long double)WIDTH;
	long double accel = 2.0 * (game->fov / 2.0 - speed * WIDTH / 2) / ((WIDTH / 2) * (WIDTH / 2));
	
	while (d_x < WIDTH)
	{
		if (ray.start <= ray.angle)
			speed += accel;
		else
			speed -= accel;
		ray.start += speed;
		ray.x = game->plr->x;// каждый раз возвращаемся в точку начала
		ray.y = game->plr->y;
		cosinus = cos(ray.start);
		sinus = sin(ray.start);
		while (game->map[(int)(ray.y)][(int)(ray.x)] != '1')//пока не воткну луч в стену
		{
			ray.x += cosinus / 100.0;
			ray.y += sinus / 100.0;
		}
		game->side_img = get_side_cub(game, &ray);//получаю указатель на одну из структур изображений
		long double range = sqrtf(powf(ray.x - game->plr->x, 2.0) + powf(ray.y - game->plr->y, 2.0)); //длина луча грязная
		ft_draw_ray(game, d_x, range,  game->plr->angle - ray.start); //рисовать столбец полностью с полом и потолком
		d_x++;//переход на след столбец камеры
	}
}


void put_men_map(t_game *game)
{
	int i = -5;
	int j = -5;

	while (i < game->k_map / 4)
	{
		j = -5;
		while (j < game->k_map / 4)
		{
			put_pixel(game->draw, (game->plr->x) * game->k_map + j, (game->plr->y) * game->k_map + i, 0x000000FF);
			j++;
		}
		i++;
	}	
}

void put_rectanlge_map(t_game *game, int x, int y, unsigned color)
{
	int i = 0;
	int j = 0;

	while (i < game->k_map)
	{
		j = 0;
		while (j < game->k_map)
		{
			put_pixel(game->draw, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_game *game)
{

	int x = 0;
	int y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			if (game->map[y][x] == '1')
				put_rectanlge_map(game, x * game->k_map, y * game->k_map, 100);
			x++;
		}
		y++;
	}
	put_men_map(game);
}

int	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	ft_cast_rays(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->draw->img, 0, 0);
	return (0);
}
