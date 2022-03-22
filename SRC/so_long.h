/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:42 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:44 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SCALE 16
# define HEIGHT 600
# define WIDTH 800
# define SO_LONG_H
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<math.h>
# include	"../libft/libft.h"
# include	"../mlx/mlx.h"

typedef struct s_img {
	void	*img;
	char	*addr; // указатель на пиксели в одномерном массиве
	int		bpp; // бит в пикселе
	int		l_len; // длина линии
	int		end; // эндиан
	int		w; // ширина кол-во пикселей
	int		h; // высота кол-во пикселей
}				t_img;

typedef struct	s_plr //структура для игрока и луча
{
	float		x; // х позиция
	float		y; // у позиция
	float		angle; // направление, куда смотрит игрок в рад вид сверху
	float		start; // левый диапазон направления в рад вид сверху
	float		end; // правый диапазон направления в рад вид сверху

}				  t_plr;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_img	*draw;
//	t_img	*space;// удалить
//	t_img	*wall;//удалить
//	t_img	*food;//удалить
//	t_img	*exit;//удалить
//	t_img	*pers;//удалить
	t_plr	*plr; // игрок
	t_img	*north_wall;
	t_img	*west_wall;
	t_img	*south_wall;
	t_img	*east_wall;
	float	x_side; // отношение отрезка от левой грани куба до точки
	// пересечения с лучем к грани куба
	float	fov; // угол обзора
	char	*map_name;
	char	**map;
//	int		move_cnt;//удалить
//	int		food_cnt;//удалить
//	int		exit_cnt;//удалить
//	int		pers_cnt;//удалить
//	int		did_move;//удалить
//	int		eat_food;//удалить
	t_img	*side_img; // куда луч смотрит, один из wall
	int		p_x; // стартовые  позиции
	int		p_y; // стартовые позиции
	int		h; // высота экрана не нужна
	int		w; // ширина экрана не нужна
	// int		need_clear;	// флаг очистки
}				t_game;


void	game_close(int err, t_game *game);
void	read_map(t_game *game, char *map_name);
int		key(int keycode, t_game *game);
int		button(t_game *game);
void	liberator(t_game	*game);
int		render(t_game *game);

#endif
