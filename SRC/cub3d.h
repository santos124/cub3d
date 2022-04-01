/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:42 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:44 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define HEIGHT 1000
# define WIDTH 2000
# define FOOT 0.2
# define FOV 90.0
# define ROTATE_ANGLE 0.2
# define CUB3D_H
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

typedef struct	s_parser {
	char	**map;
	int		col; // tebe ne nuzhno
	int		line; // tebe ne nuzhno
	int		color_bot_ceil[2][3]; //color_bot_ceil[0] - zvet pola,
	// color_bot_ceil[1] - zvet potolka
	char	*path_direction[4];// [0] - NO, [1] - SO, [2] - WE, [3] - EA
	int		tex_flag[6]; // tebe ne nuzhno
	float 	x;
	float 	y;
	float	angle;
}		t_parser;

typedef struct	s_plr //структура для игрока и луча
{
	long double		x; // х позиция
	long double		y; // у позиция
	long double		angle; // направление, куда смотрит игрок в рад вид сверху
	// WE = 0   NO = -m_pi/2  EA = pi SO = m_pi/2
	long double		start; // левый диапазон направления в рад вид сверху
	long double		end; // правый диапазон направления в рад вид сверху
}	t_plr;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_img	*draw;

	t_plr	*plr; // игрок
	t_plr	ray;
	t_img	*north_wall;
	t_img	*west_wall;
	t_img	*south_wall;
	t_img	*east_wall;
	long double	x_side; // отношение отрезка от левой грани куба до точки
	// пересечения с лучем к грани куба
	long double	fov; // угол обзора
	char	*map_name;
	char	**map;
	int		k_map;
	int		d_x;
	int		x_mouse_now;
	int		y_mouse_now;
	int		x_mouse_before;
	int		y_mouse_before;
	int		toogle_mouse;

	t_img	*side_img; // куда луч смотрит, один из wall
	long double cosinus;
	long double sinus;
	long double speed;
	long double accel;
	int		p_x; // стартовые  позиции
	int		p_y; // стартовые позиции
	int		h; // высота экрана не нужна
	int		w; // ширина экрана не нужна
	long double	cos;
	// int		need_clear;	// флаг очистки
}				t_game;


void	game_close(int err, t_game *game);
void	read_map(t_game *game, char *map_name);
int		key(int keycode, t_game *game);
int		button(t_game *game);
int		mouse_toogle(int keycode, int x, int y, t_game *game);
int		mouse_move(int x, int y, t_game *game);
void	dir_up(t_game *game);
void	dir_down(t_game *game);
void	dir_left(t_game *game);
void	dir_right(t_game *game);
void	rot_left(t_game *game);
void	rot_right(t_game *game);
void	liberator(t_game	*game);
int		render(t_game *game);
void	put_pixel(t_img *draw, int x, int y, unsigned color);
unsigned int	get_pixel(t_img *img, unsigned x, unsigned y);
void	put_men_map(t_game *game);
void	put_rectanlge_map(t_game *game, int x, int y, unsigned int color);
void	draw_minimap(t_game *game);
void	ft_cast_rays(t_game *game);
#endif