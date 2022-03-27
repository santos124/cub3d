#include "so_long.h"

int mouse_toogle(int keycode, int x, int y, t_game *game)
{
	printf("keycode=%d x=%d y=%d toogle_mouse=%d\n",keycode, x, y, game->toogle_mouse);
	if (0 == game->toogle_mouse)
		game->toogle_mouse = 1;
	else
		game->toogle_mouse = 0;
	return 0;
}

int mouse_move(int x, int y, t_game *game)
{
	
	game->x_mouse_before = game->x_mouse_now;
	game->y_mouse_before = game->y_mouse_now;
	if (game->toogle_mouse)
	{
		game->x_mouse_now = x;
		game->y_mouse_now = y;
		if (game->x_mouse_now < game->x_mouse_before)
			rot_left(game);
		else if (game->x_mouse_now > game->x_mouse_before)
			rot_right(game);
	}
	return 0;
}

int	key(int keycode, t_game *game)
{
	if (keycode == 53)
		game_close(5, game);
	else if (keycode == 0)
		dir_left(game);
	else if (keycode == 1)
		dir_down(game);
	else if (keycode == 2)
		dir_right(game);
	else if (keycode == 13)
		dir_up(game);
	else if (keycode == 123)
		rot_left(game);
	else if (keycode == 124)
		rot_right(game);
	else
		return (0);
	return (0);
}

