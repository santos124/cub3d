/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:02:17 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:02:19 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	"../libft/libft.h"
# include	"../mlx/mlx.h"

typedef struct s_img {
	void	*img;
	int		width;
	int		height;
}				t_img;

typedef struct s_enemy {
	int		x;
	int		y;
	int		d;
}				t_enemy;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_img	*space;
	t_img	*wall;
	t_img	*exit;
	t_img	**tank;
	t_img	**fuel;
	t_img	*mine;
	t_enemy	**mines;
	char	*map_name;
	char	**map;
	int		h;
	int		w;
	int		move_cnt;
	int		food_cnt;
	int		exit_cnt;
	int		pers_cnt;
	int		enemy_cnt;
	int		p_x;
	int		p_y;
	int		did_move;
	int		eat_food;
	int		need_clear;	
	int		i;
	int		j;
	int		p_d;
}				t_game;

void	init_imgs(t_game *game);
void	read_map(t_game *game, char *map_name);
void	valid_map(t_game *game);
int		button(t_game *game);
void	check_pointer(void *ptr, int err, t_game *game);
void	game_close(int err, t_game *game);
void	liberator(t_game	*game);
int		key(int keycode, t_game *game);
int		render(t_game *game);

#endif
