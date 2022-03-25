#include "so_long.h"

static void	player_look_y(int i, int j, t_all *all) // S N
{
	//x-coordinate
	//y-coordinate
	//dir x
	//dir y
	//plane x
	//plane y
	//map[i][j] = 0
}

static void	player_look_x(int i, int j, t_all *all) // E W
{
	//x-coordinate
	//y-coordinate
	//dir x
	//dir y
	//plane x
	//plane y
	//map[i][j] = 0
}

void parse_player(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'S' || all->map[i][j] == 'N')
			{
				player_look_y(i, j, all);
				return ;
			}
			if (all->map[i][j] == 'E' || all->map[i][j] == 'W')
			{
				player_look_x(i, j, all);
				return;
			}
			j++;
		}
		i++;
	}
	ft_error("Error: no player on the map!")
}
