#include "../cub3d.h"


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
	int	fd;

	i = 0;
	while (buf[i] == ' ')
		i++;
	p->path_direction[type] = ft_strdup(buf + i);
	if (!p->path_direction[type])
		ft_error("Error: malloc error!", p);
	p->tex_flag[type] += 1;
	fd = open(p->path_direction[type], O_RDONLY);
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
	while (buf[j])
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
	p->tex_flag[type + 4] += 1; // flag
	return (0);
}

int		parse_tex_and_colors(char *buf, t_parser *p)
{
	int	i;

	i = 0;
	if (p->tex_flag[0] > 1 || p->tex_flag[1] > 1 || p->tex_flag[2] > 1 ||
		p->tex_flag[3] > 1 || p->tex_flag[4] > 1 || p->tex_flag[5] > 1)
		ft_error("Error: repeatable symbols!", p);
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1 &&
		p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)
		return (-1);
	while (buf[i] == ' ')
		i++;
	if (!strncmp("NO ", buf + i, 3))
		return (get_texture(0, buf + i + 3, p));
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
