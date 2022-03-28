#include "so_long.h"

// карту добить пробелами
// записать горизонтальные и вертикальные размеры

int		check_walls(t_parse *all)
{
	int		check_line(t_all *all, int col, int line);
	int		check_column(t_all *all, int col, int line);
}


int		check_line(t_all *all, int col, int line) // 0 error; 1 norm map
{
	int i;
	int j;
	int last;

	i = 0;
	last = 0;
	while (i < col)
	{
		j = 0;
		while (j < line && all->map[i][j] == ' ')
			j++;
		if (j < line && all->map[i][j] != '1')
			return (0); // false
		j++;
		while (j < line)
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
	return (1); // norm
}

int		check_column(t_all *all, int col, int line)
{
	int	i;
	int	j;
	int	last;

	j = 0;
	last = 0;
	while (j < line)
	{
		i = 0;
		while (i < col && all->map[i][j] == ' ')
			i++;
		if (i < col && all->map[i][j] != '1')
			return (0); // false
		i++;
		while (i < col)
		{
			if (all->map[i][j] == '1')
				last = 1;
			if (all->map[i][j] == '0')
				last = 0;
			if (all->map[i][j] == ' ' && last = 0)
				return (0); // false
			if (all->map[i-1][j] == ' ' && all->map[i][j] == '0')
				return (0); //false
			i++;
		}
		if (last != 1)
			return (0); // false
		j++;
	}
	return (1); // norm
}