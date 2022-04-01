#include "so_long.h"

static void	check_map_size(t_parser *p)
{
	int		i;
	int		j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			j++;
			if (j > p->line)
				p->line = j;
		}
		i++;
	}
	p->col = i;
}

static char	*ft_realloc_mod(char *str, int num, char c)
{
	int i;
	char *new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (num + 1));
	if (!new)
		ft_error("Error: malloc error!", NULL);
	new = (char *)ft_memset(new, ' ', num);
	new[num] = '\0';
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

void	rectangle_map(t_parser *p)
{
	int	i;


	i = 0;
	while (p->map[i])
	{
		if (ft_strlen(p->map[i]) < p->line)
		{
			p->map[i] = ft_realloc_mod(p->map[i], p->line, ' '); // \0
			// dopolnitelno
			if (p->map[i] == NULL)
				ft_error("Error: malloc error!", p);
		}
		i++;
	}
}

