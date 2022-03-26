#include "so_long.h"

// карту добить пробелами

int	check_walls(t_parse *all)
{
	// check last line
	// check last column
	// check all spaces in map
}


int		check_line(t_all *all) // 0 error; j norm map must end on \0
{
	int i;
	int j;
	int last;

	i = 0;
	last = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j] == ' ')
			j++;
		if (all->map[i][j] != '1')
			return (0); // false
		j++;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				last = 1;
			if (all->map[i][j] == '0')
				last = 0;
			if (all->map[i][j] == ' ' && last = 0)
				return (0); // false
			if (all->map[i][j - 1] == ' ' && all->map[i][j] == '0')
				return (0); //false
			j++;
		}
		if (last != 1)
			return (0); // false
		i++;
	}
	return (j); // norm
}
