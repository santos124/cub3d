#include "so_long.h"

static void	player_look_y(int i, int j, t_parser *p) // S N
{
	//x-coordinate
	//y-coordinate
	//dir x
	//dir y
	//plane x
	//plane y
	//map[i][j] = 0
}

static void	player_look_x(int i, int j, t_parser *p) // E W
{
	//x-coordinate
	//y-coordinate
	//dir x
	//dir y
	//plane x
	//plane y
	//map[i][j] = 0
}

void parse_player(t_parser *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'S' || p->map[i][j] == 'N')
			{
				player_look_y(i, j, p);
				return ;
			}
			if (p->map[i][j] == 'E' || p->map[i][j] == 'W')
			{
				player_look_x(i, j, p);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error("Error: no player on the map!", p);
}
