#include "so_long.h"

void	rot_left(t_game *game)
{
	game->plr->angle -= ROTATE_ANGLE;
	if (game->plr->angle < M_PI * 2 * (-10))
		game->plr->angle = 2 * M_PI + game->plr->angle;
}

void	rot_right(t_game *game)
{
	game->plr->angle += ROTATE_ANGLE;
	if (game->plr->angle > M_PI * 2 * 10)
		game->plr->angle = 2 * M_PI - game->plr->angle;
}
