#include "so_long.h"

static void	player_look(int i, int j, t_parser *p) // S N
{
	p->x = j + 0.5;
	p->y = i + 0.5;
	if (p->map[i][j] == 'S')
		p->angle = m_pi / 2;
	if (p->map[i][j] == 'N')
		p->angle = 3 * m_pi / 2;
	if (p->map[i][j] == 'E')
		p->angle = m_pi;
	if (p->map[i][j] == 'W')
		p->angle = 0;
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
			if (p->map[i][j] == 'E' || p->map[i][j] == 'W'
				|| p->map[i][j] == 'S' || p->map[i][j] == 'N')
			{
				player_look(i, j, p);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error("Error: no player on the map!", p);
}


static void	free_all(char **all)
{
	int	i;

	i = 0;
	while (all[i])
	{
		free(all[i]);
		i++;
	}
	free(all);
}

static int	get_texture(int type, char *buf, t_parser *p)
{
	int	i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	p->path_direction[type] = ft_strdup(buf + i);
	if (!p->path_direction[type])
		ft_error("Error: malloc error!", p);
	p->tex_flag[0] = 1; //flag
	fd = open(file, O_READONLY);
	if (fd == -1)
		ft_error("Error: texture file not detected!", p);
	close(fd);
	return (0);
}

static int	get_color(int type, char *buf, t_parser *p)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	int		color;

	i = 0;
	k = 0;
	while (buf[i] == ' ')
		i++;
	j = i;
	while (!buf[j])
	{
		if (buf[j] == ',')
			k++;
		j++;
	}
	if (k != 2)
		ft_error("Error: wrong RGB value!", p);
	split = ft_split(buf + i, ',');
	while (k >= 0)
	{
		color = ft_atoi(split[k]);
		if (color >= 255 || color < 0)
			ft_error("Error: wrong RGB value!", p);
		p->color_bot_ceil[type][k] = color;
		k--;
	}
	free_all(split);
	p->tex_flag[type + 4] = 1; // flag
	return (0);
}

int		parse_tex_and_colors(char *buf, t_parser *p)
{
	int	i;

	i = 0;
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1 &&
		p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)// check
		// massiv that only one  n s e w f c
		return (ft_error("Error: repeatable symbols!", p));
	while (buf[i] == ' ')
		i++;
	if (!strncmp("NO ", buf + i, 3))
		return (get_texture(0, buf + i + 3, p)); // check texture file errors
// handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("SO ", buf + i, 3))
		return (get_texture(1, buf + i + 3, p));
	if (!strncmp("WE ", buf + i, 3))
		return (get_texture(2, buf + i + 3, p));
	if (!strncmp("EA ", buf + i, 3))
		return (get_texture(3, buf + i + 3, p));
	if (!strncmp("F ", buf + i, 2))
		return (get_color(0, buf + i + 2, p));
	if (!strncmp("C ", buf + i, 2))
		return (get_color(1, buf + i + 2, p));
	return (0);
}

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

