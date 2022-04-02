/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:00:42 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:00:44 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define HEIGHT 500
# define WIDTH 1000
# define FOOT 0.15
# define FOV 66.0
# define ROTATE_ANGLE 0.05
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
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
	int		w;
	int		h;
}				t_img;

typedef struct s_parser {
	char	**map;
	int		col;
	int		line;
	int		color_bot_ceil[2][3];
	char	*path_direction[4];
	int		tex_flag[6];
	float	x;
	float	y;
	float	angle;
}		t_parser;

typedef struct s_plr
{
	long double		x;
	long double		y;
	long double		angle;
	long double		start;
	long double		end;
}	t_plr;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		*draw;
	t_parser	*parser;
	t_plr		*plr;
	t_plr		ray;
	t_img		*north_wall;
	t_img		*west_wall;
	t_img		*south_wall;
	t_img		*east_wall;
	long double	x_side;
	long double	fov;
	char		**map;
	int			k_map;
	int			d_x;
	int			x_mouse_now;
	int			y_mouse_now;
	int			x_mouse_before;
	int			y_mouse_before;
	int			toogle_mouse;
	int			cnt_frame;
	t_img		*side_img;
	long double	cosinus;
	long double	sinus;
	long double	speed;
	long double	accel;
	long int	color_bot;
	long int	color_top;
	int			h;
	int			w;
	long double	cos;
}				t_game;

void			game_close(int err, t_game *game);
void			read_map(t_game *game, char *map_name);
t_parser		*parse_all(char *file);
void			ft_error(char *info, t_parser *p);
t_parser		*ft_init_struct(t_parser *p);
int				parse_tex_and_colors(char *buf, t_parser *p);
void			rectangle_map(t_parser *p);
int				check_walls(t_parser *p);
void			parse_player(t_parser *p);
int				key(int keycode, t_game *game);
int				button(t_game *game);
int				mouse_toogle(int keycode, int x, int y, t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			dir_up(t_game *game);
void			dir_down(t_game *game);
void			dir_left(t_game *game);
void			dir_right(t_game *game);
void			rot_left(t_game *game);
void			rot_right(t_game *game);
void			rot_left_m(t_game *game);
void			rot_right_m(t_game *game);
void			liberator(t_game	*game);
int				render(t_game *game);
void			put_pixel(t_img *draw, int x, int y, unsigned int color);
unsigned int	get_pixel(t_img *img, unsigned x, unsigned y);
void			put_men_map(t_game *game);
void			put_rectanlge_map(t_game *game, int x, int y,
					unsigned int color);
void			draw_minimap(t_game *game);
void			ft_cast_rays(t_game *game);
void			get_colors(t_game *game);
char			**ft_super_malloc(char **map, int num);
void			check_valid_char(t_parser *p);
void			check_map_format(char *file, int *fd);
#endif
