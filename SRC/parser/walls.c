#include "../cub3d.h"


static int	check_line(t_parser *p)
{
	int i;
	int j;
	int last;

	i = 0;
	last = 0;
	while (i < p->col)
	{
		j = 0;
		while (j < p->line && p->map[i][j] == ' ')
			j++;
		if (j < p->line && p->map[i][j] != '1')
			return (0);
		j++;
		while (j < p->line)
		{
			if (p->map[i][j] == '1')
				last = 1;
			if (p->map[i][j] == '0')
				last = 0;
			if (p->map[i][j] == ' ' && last == 0)
				return (0);
			if (p->map[i][j - 1] == ' ' && p->map[i][j] == '0')
				return (0);
			j++;
		}
		if (last != 1)
			return (0);
		i++;
	}
	return (1);
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
		while (i < p->col && p->map[i][j] == ' ')
			i++;
		if (i < p->col && p->map[i][j] != '1')
			return (0);
		i++;
		while (i < p->col)
		{
			if (p->map[i][j] == '1')
				last = 1;
			if (p->map[i][j] == '0')
				last = 0;
			if (p->map[i][j] == ' ' && last == 0)
				return (0);
			if (p->map[i-1][j] == ' ' && p->map[i][j] == '0')
				return (0);
			i++;
		}
		if (last != 1)
			return (0);
		j++;
	}
	return (1);
}

int		check_walls(t_parser *p)
{
	if (!check_line(p))
		return (0);
	if (!check_column(p))
		return (0);
	return (1);
}
