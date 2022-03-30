#include "so_long.h"

void	ft_error(char *info, t_parser *p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (i < 4)
		{
			if (p->path_direction[i])
				free(p->path_direction[i]);
			i++;
		}
		if (p->map)
		{
			i = 0;
			while (p->map[i])
			{
				free(p->map[i]);
				i++;
			}
			free(p->map);
		}
		free(p);
	}
	printf("%s\n", info);
	exit(1);
}
