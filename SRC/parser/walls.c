#include "so_long.h"

static int	check_line(t_parser *p) // 0 error; 1 norm map
{
	int i;
	int j;
	int last;

	i = 0;
	last = 0;
	while (i < p->col)
	{
		j = 0;
		while (j < p->line && all->map[i][j] == ' ')
			j++;
		if (j < p->line && all->map[i][j] != '1')
			return (0); // false
		j++;
		while (j < p->line)
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

static int	check_column(t_parser *p)
{
	int	i;
	int	j;
	int	last;

	j = 0;
	last = 0;
	while (j < p->line)
	{
		i = 0;
		while (i < p->col && all->map[i][j] == ' ')
			i++;
		if (i < p->col && all->map[i][j] != '1')
			return (0); // false
		i++;
		while (i < p->col)
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

int		check_walls(t_parser *p)
{
	if (!check_line(p))
		return (0);
	if (!check_column(p))
		return (0);
	return (1);
}